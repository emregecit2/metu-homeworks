#There are five helper functions in this program:
#part_list2tree: takes part_list as arguement and converts it to a tree structure.
#cphelper: takes a tree as arguement and returns an integer. helps calculate_price.
#rphelper: takes a tree and a list as arguement and returns a list. helps required_parts.
#add: takes two lists, combines them and returns a list. helps rphelper.
#deepcopy: takes any type of data and deepcopies it. helps part_list2tree.

#part_list: part list. Example: part_list=[["axle", (5, "bolt"), (7, "nut")],["bolt", 0.1],["nut", 0.15]]
#tree: a tree. Example: tree=[1, 'axle', [5, 'bolt', 0.1], [7, 'nut', 0.15]]

def calculate_price(part_list):
    return cphelper(part_list2tree(part_list))

def required_parts(part_list):
    return rphelper(part_list2tree(part_list),[])
                
def stock_check(part_list,stock_list):
    rp=required_parts(part_list)
    a=0
    while a<len(rp):
        rp[a]=(rp[a][1],rp[a][0])
        for b in range(len(stock_list)):
            if rp[a][0]==stock_list[b][1]:
                rp[a]=(rp[a][0],rp[a][1]-stock_list[b][0])
                if rp[a][1]<=0:
                    rp.remove(rp[a])
                    a-=1
                break
        a+=1
    return rp
    
def part_list2tree(part_list):
    new_list=deepcopy(part_list)
    box=[]
    while True:
        a=0
        while a<len(new_list):
            if type(new_list[a][1])==float:
                box.append(new_list.pop(a))
                a-=1
            else:
                controller=0
                for b in range(len(new_list[a][1:])):
                    if type(new_list[a][b+1])==tuple:
                        controller+=1
                        for d in range(len(box)):
                            if box[d][0]==new_list[a][b+1][1]:
                                new_list[a][b+1]=[new_list[a][b+1][0]]+box.pop(d)
                                break
                if not controller:
                    box.append(new_list.pop(a))
                    a-=1
            a+=1
        if new_list==[]:
            break
    return [1]+box[0]
            
def cphelper(tree):
    sum=0
    if type(tree[2])==float:
        sum+=tree[2]*tree[0]
    else:
        for b in range(len(tree[2:])):
            sum+=cphelper(tree[b+2])*tree[0]
    return sum

def rphelper(tree,rp):
    if type(tree[2])==float:
        add([tree[:2]],rp)
    else:
        for b in range(len(tree[2:])):
            add(rphelper(tree[b+2],[])*tree[0],rp)
    return rp

def add(lst,rp):
    for a in range(len(lst)):
        for b in range(len(rp)):
            if lst[a][1]==rp[b][1]:
                rp[b]=[rp[b][0]+lst[a][0],rp[b][1]]
                break
        else:
            rp.append(tuple(lst[a]))
    return rp

def deepcopy(item):
    if type(item)==list:
        return [deepcopy(a) for a in item]
    else:
        return item