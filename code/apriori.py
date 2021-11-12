from collections import defaultdict
from itertools import combinations
import timeit
class hashtable():
    def __init__(self,count,item_set):
            
        self.count=count
        self.item_set=item_set
        
        
class hash_apriori():
    k=0
    dataset=[]
    min_support=0
    hash_value=31
    def __init__(self,min_support):
        self.min_support=min_support

    def load_data(self,file_name):
        f=open(file_name,"r")
        line=f.readline()
        while line!="":
            line=line.split("-1")
            line=line[:-1]
            integer_map=map(int,line)
            line=set(integer_map)
            self.dataset.append(line)
            line=f.readline()

    def hash(self,item_set):
        hash_value=0
        for each in item_set:
            hash_value+=each*23
            hash_value%=self.hash_value
        return hash_value
    
    def check_subset(self,item):
        count=0
        for each_record in self.dataset:
            if item.issubset(each_record):
                count+=1
        return count

    def algorithm(self):
        hash_table=[hashtable(0,defaultdict(int)) for i in range(self.hash_value)]
        c_items_new=set()
        k_new=defaultdict(int)
        l_items_new=set()
        for each_trans in self.dataset:
            for pair in combinations(each_trans,2):
                hash_value=self.hash(pair)
                hash_table[hash_value].count+=1
                hash_table[hash_value].item_set[frozenset(pair)]+=1
        
        
        for each_hash in hash_table:
            if each_hash.count >=self.min_support:
                temp={k for (k,v) in each_hash.item_set.items() if v>=self.min_support}
                c_items_new.update(temp)

        return c_items_new


class partiton_apriori():
    def __init__(self,file_name):
        l=0
        # self.min_support=min_support
        # self.dataset=dataset
        self.file_name=file_name

    def k1_items(self,min_support,dataset):
        #print("generate_c_items")
        k1_item=defaultdict(int)
        item_set=set()
        for each_trans in dataset:
            for item in each_trans:
                k1_item[item]+=1
        #del_keys=[]
        for key,val in k1_item.items():
            #print(key,val)
            if(val>=min_support):
                item_set.add(frozenset({key}))
        return item_set

    def generate_c_items(self,itemset,k):
        #print("generate_c_items")
        c_items=set()
        pairs=[]
        for pair in combinations(itemset,2):
            temp=set().union(*pair)
            if(len(temp)==k):
                c_items.add(frozenset(temp))
        return c_items

    def algorithm(self,dataset,min_support):
        #print("algorithm")
        l1=self.k1_items(min_support,dataset)
        total_items=set()
        #print(l1)
        l_prev1=l1
        l_prev2=set()
        k=2
        while len(l_prev1)!=0:
            #print(l_prev1)
            #print(k)
            l_new=set()
            c_new=self.generate_c_items(l_prev1,k)
            #print("c_new")
            k_new=defaultdict(int)
            for each_trans in dataset:
                for each_item in c_new:
                    if each_item.issubset(each_trans):
                        k_new[each_item]+=1
            #print("k_new")
            l_new={k for (k,v) in k_new.items() if v>min_support}
            #print("l_new")
            #print("++++++++++++++++++++++++++=")
            total_items.update(l_new)
            l_prev2=l_prev1
            l_prev1=l_new
            k+=1
        return total_items

    def seq_algo(self):
        #print("seq_algo")
        itemsets=set()
        f=open(self.file_name,"r")
        line=f.readline()
        dataset=[]
        i=0
        while(line!=""):
            i+=1
            line=line.split("-1")
            line=line[:-1]
            integer_map=map(int,line)
            line=set(integer_map)
            dataset.append(sorted(line))
            line=f.readline()
            if i%1000==0:
                
                print(str(i/1000))
                start=timeit.default_timer()
                #algo=partiton_apriori(6,dataset)
                l=self.algorithm(dataset,6)
                end=timeit.default_timer()
                #print(str(end-start))
                dataset=[]
                itemsets.update(l)
                
        start=timeit.default_timer()
        #algo=partiton_apriori(6,dataset)
        l=self.algorithm(dataset,6)
        end=timeit.default_timer()
        #print(str(end-start))
        dataset=[]
        itemsets.update(l)
        return itemsets
    
    def closed_itemsets(self):
        #print("closed_itemsets")
        itemsets=self.seq_algo()
        closed_frequent_sets=set()
        itemsets=list(itemsets)
        for i in range(0,len(itemsets)-1):
            flag=1
            for j in range(i+1,len(itemsets)):
                if itemsets[i].issubset(itemsets[j]):
                    print(itemsets[i],itemsets[j])
                    flag=0
                    break
            if flag:
                closed_frequent_sets.add(itemsets[i])
        return closed_frequent_sets

    def find_global_itemsets(self,min_support):
        print("find_global_itemsets")
        c_items=defaultdict(int)
        itemsets=self.seq_algo()
        #itemsets=self.closed_itemsets()
        f=open(self.file_name,"r")
        line=f.readline()
        dataset=[]
        i=0
        while(line!=""):
            #print(i)
            i+=1
            line=line.split("-1")
            line=line[:-1]
            integer_map=map(int,line)
            line=set(integer_map)
            for each_item in itemsets:
                if each_item.issubset(line):
                    c_items[frozenset(each_item)]+=1
            line=f.readline()
        l_items={k for (k,v) in c_items.items() if v>=min_support}

        return l_items

algo=hash_apriori(360)
algo.load_data("dataset1.txt")
#k1_items,item_set=algo.k1_items()
l_items_hash=algo.algorithm()
l=partiton_apriori("dataset1.txt")
l_items_partition=l.find_global_itemsets(360)




        



            
