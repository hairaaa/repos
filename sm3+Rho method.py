#SM3
#参考资料：https://blog.csdn.net/weixin_45688634/article/details/123292997?ops_request_misc=&request_id=&biz_id=102&utm_term=sm3%E7%94%9F%E6%97%A5%E6%94%BB%E5%87%BBpython&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-123292997.142^v35^experiment_28w_180w_v1&spm=1018.2226.3001.4187
#模块模仿有些内置函数自己实现
#填充：+1+k个0+64位表l的值
import random
import math

IV = [0x7380166F, 0x4914B2B9, 0x172442D7, 0xDA8A0600, 0xA96F30BC, 0x163138AA, 0xE38DEE4D, 0xB0FB0E4E]
T = [0x79cc4519, 0x7a879d8a]

def Fill(message):
    m = bin(int(message,16))[2:]#转化为二进制，去掉0b
    while len(m)%4!=0:
        m='0'+m
    l_len=len(m)
    k_len=0
    m=m+'1'
    while (l_len +1+k_len)%512!=448:
        k_len+=1
    for i in range(0,k_len):
        m=m+'0'
    l=bin(l_len)[2:]
    while len(l)!=64:
        l='0'+l
    m=m+l
    m = hex(int(m,2))[2:]
    print("填充后的消息为:",m)
    return m

def Group(m):#分块：512bit一块==128个16进制
    n = len(m)/128
    M = []
    for i in range(int(n)):
        M.append(m[0+128*i:128+128*i])
    return M

def Expand(Message,n):#讲B扩展为132个字
    W = []#w0-w67
    W_ = []#w_0-w_63
    for j in range(16):
        W.append(int(Message[n][0+8*j:8+8*j],16))
    for j in range(16,68):
        W.append(P1(W[j-16]^W[j-9]^ROL(W[j-3],15))^ROL(W[j-13],7)^W[j-6])
    for j in range(64):
        W_.append(W[j]^W[j+4])
    return W,W_

def ROL(X,i):#左移运算
    i = i % 32
    return ((X<<i)&0xFFFFFFFF) | ((X&0xFFFFFFFF)>>(32-i))

def FF(X,Y,Z,j):
    if j>=0 and j<=15:
        return X ^ Y ^ Z
    else:
        return ((X & Y) | (X & Z) | (Y & Z))
def GG(X,Y,Z,j):
    if j>=0 and j<=15:
        return X ^ Y ^ Z
    else:
        return ((X & Y) | (~X & Z))
def P0(X):
    return X^ROL(X,9)^ROL(X,17)
def P1(X):
    return X^ROL(X,15)^ROL(X,23)
def T_(j):
    if j>=0 and j<=15:
        return T[0]
    else:
        return T[1]



def CF(V,M,i):
    A,B,C,D,E,F,G,H = V[i]
    W,W_ = Expand(M,i)
    for j in range(64):
        SS1 = ROL((ROL(A,12)+E+ROL(T_(j),j%32))%(2**32),7)
        SS2 = SS1 ^ ROL(A,12)
        TT1 = (FF(A,B,C,j)+D+SS2+W_[j])%(2**32)
        TT2 = (GG(E,F,G,j)+H+SS1+W[j])%(2**32)
        D = C
        C = ROL(B,9)
        B = A
        A = TT1
        H = G
        G = ROL(F,19)
        F = E
        E = P0(TT2)
    a,b,c,d,e,f,g,h = V[i]
    V_ = [a^A,b^B,c^C,d^D,e^E,f^F,g^G,h^H]
    return V_

def Iterate(M):
    n = len(M)
    V = []
    V.append(IV)
    for i in range(n):
        V.append(CF(V,M,i))
    return V[n]

def random_hex(length):
    result =hex(random.randint(0,16**length)).replace('0x','').upper()
    if(len(result)<length):
        result ='0'*(length-len(result))+result
    return result


def Rhomethod():#随机生成两个长度为128x4bit的数据进行生日攻击使得两串数据在进行了sm3之后杂凑值相同
    #在此只进行简单的操作，比对杂凑值的前8bit
    # 初始化一个列表,不停存入杂凑值的前8bit
    list_r = []
    message = random_hex(128)
    for i in range(256):
        # 计算出杂凑值
        m = Fill(message)  # 填充后消息
        M= Group(m)  # 数据分组
        Vn = Iterate(M)
        result = ''
        for x in Vn:
            result += (hex(x)[2:])
        print(result[:4])
        message=result
        if (result[:4]in list_r):
            print("成功找到！")
            print("其杂凑值前16bit为",result[:4])
            return 1
        else:
            list_r.append(result[:4])



if __name__ == '__main__':
    Rhomethod()



