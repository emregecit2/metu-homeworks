# 
# MODIFY get_data() AS YOU LIKE.
# DO NOT SEND THIS FILE TO US
import random
random.seed(111)  #remove hash-sign to get randomization seed we will be using at evaluation
#                    (if you fix the seed you get always the same probabilty choice sequence)
def f(sayi,oran,M,N):
    mask=["masked","notmasked"]
    lst=[]
    for a in range(sayi):
        lst.append([(),random.randrange(0,8),random.choice(mask),random.choices(["infected","notinfected"],weights=[oran,1-oran])[0]])
        lst[a][0]=controller(a,lst,M,N)
    return(lst)
def controller(a,lst,M,N):
    coordinates=(random.randrange(0,N),random.randrange(0,M))
    for b in range(a):
        if lst[b][0]==coordinates: return controller(a,lst,M,N)
    else: return coordinates
def g():
    sayi=10
    oran=0.5
    lst=["M","N","D","K","LAMBDA","MU"]
    lst2=[50,100,5,80,30,0.55]
    print("\nProgramın çalışması için gerekli değişkenleri girmeniz istenecek.\nBir değişkenin varsayılan değerini kullanmak istiyorsanız değer girmeniz istendiğinde hiçbirşey yazmadan enter'a basın.\nVarsayılan değerler şu şekildedir:\nM=50, N=100, D=5, K=80, LAMBDA=30, MU=0.55, kişi sayısı=10, bireyin enfekte başlama ihtimali=0.5, DELAY=1000\nDevam etmek için enter'a basın.")
    input()
    for a in range(6):
        b=input("%s="%lst[a])
        if b: lst2[a]=eval(b)
    a=input("kişi sayısı=")
    if a: sayi=int(a)
    a=input("bireyin enfekte başlama ihtimali=")
    if a: oran=eval(a)
    M=lst2[0]
    N=lst2[1]
    D=lst2[2]
    K=lst2[3]
    LAMBDA=lst2[4]
    MU=lst2[5]
    return [M,N,D,K,LAMBDA,MU]+[f(sayi,oran,M,N)]
def delay():
    if x: print("DELAY değerini giriniz. Varsayılan değeri kullanmak istiyorsanız hiçbirşey yazmadan enter'a basın.\nVarsayılan DELAY=1000.")
    a=input("DELAY=")
    if a: return eval(a)
    else: return 1000
x=int(input("yeni dünya oluştur(0)/ dünya numarasını gir(1/2/3...): "))
if not x: a=g()
def get_data():
    if not x: return a
    if x==1: return[50, 100, 5, 80, 30, 0.55, [[(22, 14), 0, 'notmasked', 'notinfected'], [(19, 15), 7, 'notmasked', 'notinfected'], [(17, 16), 7, 'notmasked', 'notinfected'], [(26, 20), 3, 'notmasked', 'infected'], [(22, 21), 5, 'masked', 'infected'], [(25, 21), 3, 'notmasked', 'infected']]]
    if x==2: return[50, 100, 5,  80,  30,  0.55,  [[(34, 21), 4, 'notmasked', 'notinfected'] , [(27, 28), 2, 'notmasked', 'notinfected'] , [(40, 28), 6, 'notmasked', 'infected'] , [(34, 33), 2, 'masked', 'notinfected']]]
    if x==3: return[100, 100, 5,  70,  30,  0.50,  [[(12, 18), 5, 'masked', 'infected'] , [(25, 30), 3, 'notmasked', 'infected'] , [(50, 40), 1, 'notmasked', 'notinfected'] , [(66, 10), 7, 'masked', 'notinfected']]]
    if x==4: return[50, 100, 5, 80, 30, 0.55, [[(3, 38), 0, 'notmasked', 'infected'], [(7, 41), 1, 'notmasked', 'infected'], [(92, 41), 7, 'notmasked', 'infected'], [(1, 43), 2, 'notmasked', 'notinfected'], [(98, 44), 6, 'notmasked', 'notinfected'], [(8, 45), 2, 'notmasked', 'infected'], [(91, 45), 6, 'notmasked', 'infected'], [(2, 47), 1, 'notmasked', 'notinfected'], [(6, 48), 0, 'notmasked', 'notinfected'], [(91, 48), 6, 'notmasked', 'infected'], [(97, 48), 7, 'notmasked', 'notinfected']]]
    if x==9: return[1, 29, 8, 4, 72, 0.26, [[(5, 0), 3, 'masked', 'infected'], [(13, 0), 4, 'masked', 'notinfected'], [(15, 0), 3, 'masked', 'notinfected'], [(10, 0), 4, 'masked', 'notinfected'], [(21, 0), 3, 'notmasked', 'infected'], [(2, 0), 5, 'masked', 'notinfected'], [(12, 0), 2, 'masked', 'infected'], [(26, 0), 5, 'masked', 'notinfected'], [(4, 0), 4, 'notmasked', 'notinfected'], [(8, 0), 4, 'notmasked', 'infected'], [(27, 0), 6, 'notmasked', 'infected'], [(20, 0), 2, 'masked', 'infected'], [(18, 0), 4, 'notmasked', 'infected'], [(28, 0), 5, 'notmasked', 'infected'], [(14, 0), 5, 'masked', 'infected'], [(19, 0), 3, 'notmasked', 'infected'], [(22, 0), 4, 'notmasked', 'notinfected'], [(6, 0), 2, 'notmasked', 'infected'], [(11, 0), 3, 'notmasked', 'notinfected'], [(0, 0), 3, 'masked', 'infected'], [(23, 0), 5, 'masked', 'infected'], [(7, 0), 4, 'masked', 'infected'], [(25, 0), 6, 'notmasked', 'infected'], [(16, 0), 2, 'notmasked', 'infected'], [(24, 0), 2, 'masked', 'notinfected'], [(17, 0), 6, 'masked', 'infected'], [(9, 0), 5, 'masked', 'notinfected'], [(3, 0), 3, 'notmasked', 'notinfected']]]