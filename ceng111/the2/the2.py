import random
from evaluator import *    # get_data() will come from this import

[M,N,D,K,LAMBDA,MU,universal_state]=get_data()

def new_move():
	for y in range(len(universal_state)):#this loop applies the movement rules
		tv=universal_state[y][:] #tv: temporary value
		tv[1]-=random.choices([8,7,6,5,4,3,2,1],weights=[1/2*MU,1/8*MU,1/2*(1-MU-MU**2),2/5*MU**2,1/5*MU**2,2/5*MU**2,1/2*(1-MU-MU**2),1/8*MU])[0] #if random.choices returns [2], it means left. left changes your direction 6 units in counter clockwise direction. others are similar.if we substract that from tv[1], we can get the direction we want.
		tv[1]=[0,1,2,3,4,5,6,7][tv[1]] # i'm using negative indexing property of lists because if tv[1]=-3 it is actally 5.
		lst_coded=[[0,1],[-1,1],[-1,0],[-1,-1],[0,-1],[1,-1],[1,0],[1,1]] #I defined a coded list which encodes "where to move" data in [x,y] form. If x is positive that means x will increase by one.
		tv[0]=(tv[0][0]+lst_coded[tv[1]][0],tv[0][1]+lst_coded[tv[1]][1])
		for controller in universal_state: #after here, i check if there is any other indivudual where we want to go. if there is no individual, we can finally go there.
			if controller[0]==tv[0]: break
		else:
			if 0<=tv[0][0]<N and 0<=tv[0][1]<M: universal_state[y]=tv
	tv=[]#tv: temporary value
	for y in range(len(universal_state)):#this loop applies the contamination rules.
			for x in range(y+1,len(universal_state)):#each individual interacts with just the individuals before him, thus no individuals interact more than once. 
				distance=((universal_state[y][0][0]-universal_state[x][0][0])**2+(universal_state[y][0][1]-universal_state[x][0][1])**2)**(1/2)
				if distance<=D and not universal_state[y][3]==universal_state[x][3]:#if noone is infected, no contamination. if both are infected no contanimation.
						probability=min(1,K/(distance**2))*mask(x)*mask(y)
						if random.choices([1,0],weights=[probability,1-probability])[0]: #I use a temporary list thus infected individuals can't start infecting others immediately.
							tv.append(x)
							tv.append(y)
	for y in tv: #here, after the contamination rules are applied for everybody, I can change the infection status.
		universal_state[y][3]="infected"
	return universal_state

def mask(x):
	if universal_state[x][2]=="masked": return 1/LAMBDA
	else: return 1