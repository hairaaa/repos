#include<iostream>
#include<cmath>
#include<cstdlib>
#include <stdlib.h>
#include<ctime>
#include<string>
#include<Windows.h>
using namespace std;
DWORD start, finish;


string to16(int* x)//二进制转为16进制
{
	string p;
	for (int i = 0; i < 32; i += 4)
	{
		if (x[i] == 0)
		{
			if (x[i + 1] == 0)
			{
				if (x[i + 2] == 0)
				{
					if (x[i + 3] == 0)
						p.append("0");
					else
						p.append("1");
				}
				else
				{
					if (x[i + 3] == 0)
						p.append("2");
					else
						p.append("3");
				}
			}
			else
			{
				if (x[i + 2] == 0)
				{
					if (x[i + 3] == 0)
						p.append("4");
					else
						p.append("5");
				}
				else
				{
					if (x[i + 3] == 0)
						p.append("6");
					else
						p.append("7");
				}
			}
		}
		else
		{
			if (x[i + 1] == 0)
			{
				if (x[i + 2] == 0)
				{
					if (x[i + 3] == 0)
						p.append("8");
					else
						p.append("9");
				}
				else
				{
					if (x[i + 3] == 0)
						p.append("A");
					else
						p.append("B");
				}
			}
			else
			{
				if (x[i + 2] == 0)
				{
					if (x[i + 3] == 0)
						p.append("C");
					else
						p.append("D");
				}
				else
				{
					if (x[i + 3] == 0)
						p.append("E");
					else
						p.append("F");
				}
			}
		}
	}
	return p;
}

void to2(string p1, int* x)//16进制转为二进制
{
	int temp1;
	char e;
	for (int f = 0; f <= p1.length(); f++)
	{
		temp1 = 4 * f;
		e = p1[f];
		if (e >= 'A' && e <= 'F')
		{
			int a = static_cast<int>(e - 'F' + 15);
			switch (a)
			{
			case 10:x[temp1] = 1; x[temp1 + 1] = 0; x[temp1 + 2] = 1; x[temp1 + 3] = 0; break;
			case 11:x[temp1] = 1; x[temp1 + 1] = 0; x[temp1 + 2] = 1; x[temp1 + 3] = 1; break;
			case 12:x[temp1] = 1; x[temp1 + 1] = 1; x[temp1 + 2] = 0; x[temp1 + 3] = 0; break;
			case 13:x[temp1] = 1; x[temp1 + 1] = 1; x[temp1 + 2] = 0; x[temp1 + 3] = 1; break;
			case 14:x[temp1] = 1; x[temp1 + 1] = 1; x[temp1 + 2] = 1; x[temp1 + 3] = 0; break;
			case 15:x[temp1] = 1; x[temp1 + 1] = 1; x[temp1 + 2] = 1; x[temp1 + 3] = 1; break;
			}
		}
		else if (isdigit(e))
		{
			int b = static_cast<int>(e - '0');
			switch (b)
			{
			case 0:x[temp1] = 0; x[temp1 + 1] = 0; x[temp1 + 2] = 0; x[temp1 + 3] = 0; break;
			case 1:x[temp1] = 0; x[temp1 + 1] = 0; x[temp1 + 2] = 0; x[temp1 + 3] = 1; break;
			case 2:x[temp1] = 0; x[temp1 + 1] = 0; x[temp1 + 2] = 1; x[temp1 + 3] = 0; break;
			case 3:x[temp1] = 0; x[temp1 + 1] = 0; x[temp1 + 2] = 1; x[temp1 + 3] = 1; break;
			case 4:x[temp1] = 0; x[temp1 + 1] = 1; x[temp1 + 2] = 0; x[temp1 + 3] = 0; break;
			case 5:x[temp1] = 0; x[temp1 + 1] = 1; x[temp1 + 2] = 0; x[temp1 + 3] = 1; break;
			case 6:x[temp1] = 0; x[temp1 + 1] = 1; x[temp1 + 2] = 1; x[temp1 + 3] = 0; break;
			case 7:x[temp1] = 0; x[temp1 + 1] = 1; x[temp1 + 2] = 1; x[temp1 + 3] = 1; break;
			case 8:x[temp1] = 1; x[temp1 + 1] = 0; x[temp1 + 2] = 0; x[temp1 + 3] = 0; break;
			case 9:x[temp1] = 1; x[temp1 + 1] = 0; x[temp1 + 2] = 0; x[temp1 + 3] = 1; break;
			}

		}
	}
}

string x_or(string p1, string p2)//异或
{
	int X1[32];
	int X2[32];
	to2(p1, X1);
	to2(p2, X2);
	int temp = 0;
	for (int i = 0; i <32; i++)
	{
		temp = *(X1 + i) + *(X2 + i);
		temp = temp - (temp / 2) * 2;
		*(X1 + i) = temp;
	}
	return to16(X1);
}


/*=======================Loop_Move循环左移============================*/
void loop_move(int* p, int x)//移位
{
	int q[32];
	int temp1=0;
	for (int i = 0; i < 32 - x; i++)
	{
		q[i] = p[i+x];
		temp1 = i;
		temp1++;
	}
	for (int i = 0; i < x; i++)
	{
		q[temp1] = p[i];
		temp1++;
	}
	for (int i = 0; i < 32; i++)
	{
		*(p + i) = q[i];
	}
}



/*=======================Dcm_Binary_Swap十进制转为二进制============================*/

void db_swap(int dcm, int* p)
{
	int temp1 = dcm;
	int temp2;
	for (int i = 3; i >= 0; i--)
	{
		temp2 = temp1 / 2;
		temp1 = temp1 - temp2 * 2;
		*(p + i) = temp1;
		temp1 = temp2;
	}



}



class sm42;//加密
class ides;//解密

/*=================================产生32个子秘钥======================================*/

class sm4//用来产生32个子密钥
{
private:
	string MK[4];//原始密钥分组
	string K[36];
	string rk[32];//rk密钥
	string a[4];//用于轮函数实现
	string b[4];
	string cc;

public:
	sm4();
	friend sm42;
	friend ides;
};
sm4::sm4()
{
	int i, j;
	int f, c;
	//cout << "密钥为： ";//密钥32个字符
	string miyao = "0123456789ABCDEFFEDCBA9876543210";
	//cout << miyao.substr(0, 8) << " " << miyao.substr(8, 8) << " " << miyao.substr(16, 8) << " " << miyao.substr(24, 8) << endl;


	

	f = 0;
	for (i = 0; i < 32; i += 8)
	{
		MK[f] = miyao.substr(i, 8);//分组
		f++;
	}

	//这些参数固定
	string FK[4] = { "A3B1BAC6", "56AA3350", "677D9197", "B27022DC" };
	string CK[32] = { "00070E15", "1C232A31", "383F464D", "545B6269",
					  "70777E85", "8C939AA1", "A8AFB6BD", "C4CBD2D9",
					  "E0E7EEF5", "FC030A11", "181F262D", "343B4249",
					  "50575E65", "6C737A81", "888F969D", "A4ABB2B9",
					  "C0C7CED5", "DCE3EAF1", "F8FF060D", "141B2229",
					  "30373E45", "4C535A61", "686F767D", "848B9299",
					  "A0A7AEB5", "BCC3CAD1", "D8DFE6ED", "F4FB0209",
					  "10171E25", "2C333A41", "484F565D", "646B7279" };
	
	


	for (i = 0; i < 4; i++)
	{
		K[i]=x_or(MK[i],FK[i]);//异或
	}
	
	string Sbox[16][16] = { {"D6","90","E9","FE","CC","E1","3D","B7","16","B6","14","C2","28","FB","2C","05"},
					 {"2B","67","9A","76","2A","BE","04","C3","AA","44","13","26","49","86","06","99"},
					 {"9C","42","50","F4","91","EF","98","7A","33","54","0B","43","ED","CF","AC","62"},
					 {"E4","B3","1C","A9","C9","08","E8","95","80","DF","94","FA","75","8F","3F","A6"},
					 {"47","07","A7","FC","F3","73","17","BA","83","59","3C","19","E6","85","4F","A8"},
					 {"68","6B","81","B2","71","64","DA","8B","F8","EB","0F","4B","70","56","9D","35"},
					 {"1E","24","0E","5E","63","58","D1","A2","25","22","7C","3B","01","21","78","87"},
					 {"D4","00","46","57","9F","D3","27","52","4C","36","02","E7","A0","C4","C8","9E"},
					 {"EA","BF","8A","D2","40","C7","38","B5","A3","F7","F2","CE","F9","61","15","A1"},
					 {"E0","AE","5D","A4","9B","34","1A","55","AD","93","32","30","F5","8C","B1","E3"},
					 {"1D","F6","E2","2E","82","66","CA","60","C0","29","23","AB","0D","53","4E","6F"},
					 {"D5","DB","37","45","DE","FD","8E","2F","03","FF","6A","72","6D","6C","5B","51"},
					 {"8D","1B","AF","92","BB","DD","BC","7F","11","D9","5C","41","1F","10","5A","D8"},
					 {"0A","C1","31","88","A5","CD","7B","BD","2D","74","D0","12","B8","E5","B4","B0"},
					 {"89","69","97","4A","0C","96","77","7E","65","B9","F1","09","C5","6E","C6","84"},
					 {"18","F0","7D","EC","3A","DC","4D","20","79","EE","5F","3E","D7","CB","39","48"} };
	

	

	for (i = 0; i < 32; i++)
	{
		int s1[4][8];
		int temp=0;
		string m;
		rk[i] = x_or(K[i + 1], K[i + 2]);
		rk[i] = x_or(rk[i], K[i + 3]);
		rk[i] = x_or(rk[i], CK[i]);
		for (j = 0; j < 4; j++)
		{
			a[j] = rk[i].substr(temp, 2);
			temp += 2;
		}
		for (j = 0; j < 4; j++)
		{
			to2(a[j], s1[j]);
			f = s1[j][0] * 8 + s1[j][1] * 4 + s1[j][2] * 2 + s1[j][3];//行
			c = s1[j][4] * 8 + s1[j][5] * 4 + s1[j][6] * 2 + s1[j][7];//表的列
			m = Sbox[f][c];
			b[j].append(m);
		}
		for (j = 0; j < 4; j++)
		{
			cc.append(b[j]);
		}
		for (j = 0; j < 4; j++)
		{
			string().swap(a[j]);
			string().swap(b[j]);
		}
		
		int cx1[32];
		int cx2[32];
		int cx3[32];
		//算循环展开，牺牲了内存
		to2(cc, cx1);
		to2(cc, cx2);
		to2(cc, cx3);
		loop_move(cx1, 13);//移位
		loop_move(cx2, 23);
		m=x_or(x_or(to16(cx2),to16(cx1)), to16(cx3));
		K[i + 4] = x_or(m, K[i]);
		rk[i] = K[i+4];
		string().swap(cc);
	}
}








/*=======================加密============================*/
//giveM 加密算法
class sm42
{
public:
	sm42();
	void giveM(char*);//提出加密结果

private:
	string K[32];//32轮密钥
	string X[36];//明文X0...X35
	string a[4];//用于实现轮函数
	string b[4];//用于实现轮函数
	string cc;
	string miwen;//结果
};
sm42::sm42()
{
	int i, j;
	int f, c;
	//cout << "明文为： ";//明文32个字符
	string mingwen = "0123456789ABCDEFFEDCBA9876543210";
	//cout << mingwen.substr(0, 8) << " " << mingwen.substr(8, 8) << " " << mingwen.substr(16, 8) << " " << mingwen.substr(24, 8) << endl;

	f = 0;
	for (i = 0; i < 32; i+=8)//分组
	{
		X[f] = mingwen.substr(i, 8);
		f++;
	}
	


	sm4 jm;//定义“用于产生16个子秘钥的”对象

	for (i = 0; i <= 31; i++)
	{
		K[i] = jm.rk[i];//获取密钥
	}
	string Sbox[16][16] = { {"D6","90","E9","FE","CC","E1","3D","B7","16","B6","14","C2","28","FB","2C","05"},
					 {"2B","67","9A","76","2A","BE","04","C3","AA","44","13","26","49","86","06","99"},
					 {"9C","42","50","F4","91","EF","98","7A","33","54","0B","43","ED","CF","AC","62"},
					 {"E4","B3","1C","A9","C9","08","E8","95","80","DF","94","FA","75","8F","3F","A6"},
					 {"47","07","A7","FC","F3","73","17","BA","83","59","3C","19","E6","85","4F","A8"},
					 {"68","6B","81","B2","71","64","DA","8B","F8","EB","0F","4B","70","56","9D","35"},
					 {"1E","24","0E","5E","63","58","D1","A2","25","22","7C","3B","01","21","78","87"},
					 {"D4","00","46","57","9F","D3","27","52","4C","36","02","E7","A0","C4","C8","9E"},
					 {"EA","BF","8A","D2","40","C7","38","B5","A3","F7","F2","CE","F9","61","15","A1"},
					 {"E0","AE","5D","A4","9B","34","1A","55","AD","93","32","30","F5","8C","B1","E3"},
					 {"1D","F6","E2","2E","82","66","CA","60","C0","29","23","AB","0D","53","4E","6F"},
					 {"D5","DB","37","45","DE","FD","8E","2F","03","FF","6A","72","6D","6C","5B","51"},
					 {"8D","1B","AF","92","BB","DD","BC","7F","11","D9","5C","41","1F","10","5A","D8"},
					 {"0A","C1","31","88","A5","CD","7B","BD","2D","74","D0","12","B8","E5","B4","B0"},
					 {"89","69","97","4A","0C","96","77","7E","65","B9","F1","09","C5","6E","C6","84"},
					 {"18","F0","7D","EC","3A","DC","4D","20","79","EE","5F","3E","D7","CB","39","48"} };




	for (i = 0; i < 32; i++)
	{
		int s1[4][8];
		int temp = 0;
		string m;
		for (i = 0; i < 32; i++)//轮函数
		{
			int temp = 0;
			string m;
			X[i + 4] = x_or(X[i + 1], X[i + 2]);
			X[i + 4] = x_or(X[i + 4], X[i + 3]);
			X[i + 4] = x_or(X[i + 4], K[i]);
			for (j = 0; j < 4; j++)
			{
				a[j] = X[i + 4].substr(temp, 2);
				temp += 2;
			}
			for (j = 0; j < 4; j++)
			{
				to2(a[j], s1[j]);
				f = s1[j][0] * 8 + s1[j][1] * 4 + s1[j][2] * 2 + s1[j][3];//行
				c = s1[j][4] * 8 + s1[j][5] * 4 + s1[j][6] * 2 + s1[j][7];//表的列
				m = Sbox[f][c];//S盒替换
				b[j].append(m);
			}
			for (j = 0; j < 4; j++)
			{
				cc.append(b[j]);
			}
			for (j = 0; j < 4; j++)
			{
				string().swap(a[j]);
				string().swap(b[j]);
			}
			int cx1[32];
			int cx2[32];
			int cx3[32];
			int cx4[32];
			int cx5[32];
			//这样在一定情况下算循环展开
			to2(cc, cx1);//转为2进制（16->2)
			to2(cc, cx2);
			to2(cc, cx3);
			to2(cc, cx4);
			to2(cc, cx5);
			string().swap(cc);
			loop_move(cx1, 2);//左移
			loop_move(cx2, 10);
			loop_move(cx3, 18);
			loop_move(cx4, 24);
			m = x_or(x_or(x_or(x_or(to16(cx2), to16(cx1)), to16(cx3)), to16(cx4)),to16(cx5));//得出结果
			X[i + 4] =x_or(m,X[i]);
		}
	}
	miwen.append(X[35]);//移位
	miwen.append(X[34]);
	miwen.append(X[33]);
	miwen.append(X[32]);
	//cout << "结果为： " << miwen.substr(0, 8) <<" "<< miwen.substr(8, 8)<<" "<< miwen.substr(16, 8)<<" "<< miwen.substr(24, 8)<< endl;


}

void sm42::giveM(char *p)//提出密文
{
	for (int i = 0; i < 32; i++)
	{
		*(p + i) = miwen[i];
	}
}



/*========================================解密=================================*/
class ides
{
public:
	ides();
	string K[32];//密钥
	string C[36];
	string MK[4];
	string a[4];
	string b[4];
	string cc;
	string jiemi;
	void getw(string);//获得密文
};
ides::ides()
{
	int i, j;
	int f, c;
	
	sm4 jm1;
	for (int i = 0; i <= 31; i++)
	{
		K[i] = jm1.rk[31 - i];//倒序取密钥
	}

}

void ides::getw(string miwen)
{
	int i, j, c;
	int f = 0;
	for (int i = 0; i < 32; i += 8)
	{
		C[f] = miwen.substr(i, 8);
		f++;
	}
	string Sbox[16][16] = { {"D6","90","E9","FE","CC","E1","3D","B7","16","B6","14","C2","28","FB","2C","05"},
					 {"2B","67","9A","76","2A","BE","04","C3","AA","44","13","26","49","86","06","99"},
					 {"9C","42","50","F4","91","EF","98","7A","33","54","0B","43","ED","CF","AC","62"},
					 {"E4","B3","1C","A9","C9","08","E8","95","80","DF","94","FA","75","8F","3F","A6"},
					 {"47","07","A7","FC","F3","73","17","BA","83","59","3C","19","E6","85","4F","A8"},
					 {"68","6B","81","B2","71","64","DA","8B","F8","EB","0F","4B","70","56","9D","35"},
					 {"1E","24","0E","5E","63","58","D1","A2","25","22","7C","3B","01","21","78","87"},
					 {"D4","00","46","57","9F","D3","27","52","4C","36","02","E7","A0","C4","C8","9E"},
					 {"EA","BF","8A","D2","40","C7","38","B5","A3","F7","F2","CE","F9","61","15","A1"},
					 {"E0","AE","5D","A4","9B","34","1A","55","AD","93","32","30","F5","8C","B1","E3"},
					 {"1D","F6","E2","2E","82","66","CA","60","C0","29","23","AB","0D","53","4E","6F"},
					 {"D5","DB","37","45","DE","FD","8E","2F","03","FF","6A","72","6D","6C","5B","51"},
					 {"8D","1B","AF","92","BB","DD","BC","7F","11","D9","5C","41","1F","10","5A","D8"},
					 {"0A","C1","31","88","A5","CD","7B","BD","2D","74","D0","12","B8","E5","B4","B0"},
					 {"89","69","97","4A","0C","96","77","7E","65","B9","F1","09","C5","6E","C6","84"},
					 {"18","F0","7D","EC","3A","DC","4D","20","79","EE","5F","3E","D7","CB","39","48"} };

	for (i = 0; i < 32; i++)
	{
		int s1[4][8];
		int temp = 0;
		string m;
		for (i = 0; i < 32; i++)
		{
			int temp = 0;
			string m;
			C[i + 4] = x_or(C[i + 1], C[i + 2]);
			C[i + 4] = x_or(C[i + 4], C[i + 3]);
			C[i + 4] = x_or(C[i + 4], K[i]);
			for (j = 0; j < 4; j++)
			{
				a[j] = C[i + 4].substr(temp, 2);
				temp += 2;
			}
			for (j = 0; j < 4; j++)
			{
				to2(a[j], s1[j]);
				f = s1[j][0] * 8 + s1[j][1] * 4 + s1[j][2] * 2 + s1[j][3];//行
				c = s1[j][4] * 8 + s1[j][5] * 4 + s1[j][6] * 2 + s1[j][7];//中间组成十进制数作为表的列
				m = Sbox[f][c];
				b[j].append(m);
			}
			for (j = 0; j < 4; j++)
			{
				cc.append(b[j]);
			}
			for (j = 0; j < 4; j++)
			{
				string().swap(a[j]);
				string().swap(b[j]);
			}
			int cx1[32];
			int cx2[32];
			int cx3[32];
			int cx4[32];
			int cx5[32];
			to2(cc, cx1);
			to2(cc, cx2);
			to2(cc, cx3);
			to2(cc, cx4);
			to2(cc, cx5);
			string().swap(cc);
			loop_move(cx1, 2);
			loop_move(cx2, 10);
			loop_move(cx3, 18);
			loop_move(cx4, 24);
			m = x_or(x_or(x_or(x_or(to16(cx2), to16(cx1)), to16(cx3)), to16(cx4)), to16(cx5));
			C[i + 4] = x_or(m,C[i]);
		}
	}
	jiemi.append(C[35]);
	jiemi.append(C[34]);
	jiemi.append(C[33]);
	jiemi.append(C[32]);
	//cout << "解密后： " << jiemi.substr(0, 8) << " " << jiemi.substr(8, 8) << " " << jiemi.substr(16, 8) << " " << jiemi.substr(24, 8) << endl;
}















int main()
{
	cout << "运行10000次使用时间：" << endl;
	char miwen[32];
	char miyao[32][32];
	start = GetTickCount64();
	for (int q = 0; q < 10000; q++)
	{
		sm42 sm2;
		//cout << endl;
		//finish = GetTickCount64();		//用时

		//printf("加密用：%f s ", float(finish - start) / 1000);
		//cout << endl;
		

		sm2.giveM(miwen);
		//start = GetTickCount64();
		ides am;
		am.getw(miwen);
		
	}
	finish = GetTickCount64();
	printf("加解密用时：%f s\n ", float(finish - start) / 1000);
	//printf("解密用：%f s\n ", float(finish - start) / 1000);
	return 0;

}


