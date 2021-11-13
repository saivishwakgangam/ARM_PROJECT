# Apriori
## Dataset Stats
Dataset Name: BMSWEBVIEW1
The dataset used for this experiment contains click stream data from an e-commerce. In this dataset, the sequence count is 59,601 and item count is 497.


## Hash Based Technique
### Implementation
Hash based technique is implemented only for 2-item sets as mentioned in the pdf.
1) Hash table is created with size 31.
2) When scanning the dataset for 1-itemsets ,we can directly get 2-itemsets.
3) For each 2-itemset, a hash value is computed with mod 31. Using the hash value, we can directly push itemset to respective bucket.
4) While finding frequent itemsets, we can ignore the buckets with count less than min support.
5) From these candidate items, we can easily find itemsets with min support.
6) By using hash table, The number of candidate items are decreased. So the efficiency is more than normal apriori.

## Run time analysis


| Algorithm | With Out Hash table| With hash table | 
| :---: | :---: | :---: | 
| Candidate items count | 89681 | 63973 |


1)We can observe that,there is significant decrease in number of candidate items. If we implement same for all itemsets, there will be significant improvement in run time with hash based technique.
2)for 2-item sets, Difference in runtime for hash based and normal apriori is negligible.






## Partitioning
### Dataset split
The entire dataset is divide into some (tried different partitions ) partitions and basic apriori algorithm is run on each partition sequentially. Once local frequent itemsets are found, the entire dataset is scanned again to find global frequent items sets. From these frequent global frequent items, Closed frequents itemsets are mined .


### Implementation
1) For each partition, algorithm scans all transactions to count number of occurences of each item. The items with count less than minimum support are discarded.
2) From frequent 1-item sets, 2-items sets are computed by
   finding combinations of all items. Algorithm scans all transactions again to count all occurences of each 2-item.
   The items with count less than minimum support are discarded as done above.
3) Step 2 is repeated till there are no k-items sets with count at least equal to min support. Then k-1-item sets are returned. These are closed frequent items for each partition.
4) Once all local frequent item sets are computed, global frequent itemsets are found by scanning entire dataset again.

## Run time analysis
Partition count=20

| Min Support | 0.1 | 0.05  | 0.01 |
| :---: | :---: | :---: | :---: | 
| Run Time | 1 sec | 3 sec | 30 sec |

We can observe that with decreasing min support ,run time is increasing. In this experiment, each partition was run using normal apriori.
we observed runtime using apriori library and it has nearly same runtime.


# FP GROWTH

### Dataset Stats
The dataset used for this experiment contains click stream data from an e-commerce. In this dataset, the sequence count is 59,601 and item count is 497.

### ALGORITHM(FP TREE CONSTRUCTION)
- Initially we read the database and individual count of each item is calculated. Now after observing the count values
  we decided the minimum support count to be 360 and minimum support is 0.006.
- Now items are sorted based on their frequency from highest to lowest and each transaction is sorted in the order of item
  sets.
- After sorting the transactions,fp(frequent pattern) tree is constructed maintaining node count,next link(for mining purpose),and parent(for mining purpose) for each node.

### ALGORITHM(FP TREE MINING)
- Now after construction of FP Tree FP growth algorithm is implemented on constructed FP Tree.
- Each path is mined recursively for this we followed text book algorithm.
- Then we calculated frequent item sets, from frequent item sets we calculated closed frequent item sets.

### RUNTIME ANALYSIS
- For a data with item count 129 after removing items with less support count and number of transactions 50718 it took around
  3 sec to generate closed frequent item sets and we observed runtime using fp growth library and it has nearly same runtime.

