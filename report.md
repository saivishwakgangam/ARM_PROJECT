# Apriori
## dataset stats
The dataset used for this experiment contains clickstrem data from an e-commerce. In this dataset, the sequemce count is 59,601 and item count is 497.


## Hash Based Technique
### Implementation
Hash based technique is implemented only for 2-item sets as mentioned in the pdf.
1) Hash table is created with size 31.
2) When scanning the dataset for 1-itemsets ,we can direclty get 2-itemsets.
3) For each 2-itemset, a hash values is computed with mod 31. Using the hash value, we can direclty push itemset to respective bucket.
4) While finding frequent itemsets, we can ignore the buckets with count less than min support.
5) From these candidate items, we can easily find itemsets with min support.
6) By using hash table, The number of candidte items are decreased. So the efficiency is more than normal apriori.

## Run time analysis 


| Algorithm | With Out Hash table| With hash table | 
| :---: | :---: | :---: | 
| Candidate items count | 89681 | 63973 |

We can observe that,these is significant decrease in number of candidate items. If we implement same for all itemsets, there will be significant improvement in hash based technique.





## Partitioning
### Dataset split
The entire dataset is divide into some (tried different partitions ) partitons and basic apriori algorithm is run on each partiton sequentially. Once local frequent itemsets are found, the entire dataset is scanned again to find global frequent items sets. From these frequent global frequent items, Closed frequents itemsets are mined .


### Implementation
1) For each partition, algorithm scans all transactions to count number of occurences of each item. The items with count less than minimum support are discarded. 
2) From frequent 1-itemsets, 2-items sets are computed by 
finding combiantions of all items. Algorithm scans all transactions again to count all occurences of each 2-item.
The items with count less than minimum support are discarded as done above.
3) Step 2 is repeated till there are no k-items sets with count atleast equal to min support. Then k-1-item sets are returned. These are closed frequent items for each partition.
4) Once all local frequent item sets are computed, global frequent itemsets are found by scanning entire dataset again.

## Run time analysis 
