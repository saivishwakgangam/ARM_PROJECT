# Apriori
## dataset stats
The dataset used for this experiment contains clickstrem data from an e-commerce. In this dataset, the sequemce count is 59,601 and item count is 497.

## Run time analysis 


## Hash Based Technique



## Partitioning
### Dataset split
The entire dataset is divide into 60 partitons and basic apriori algorithm is run on each partiton sequentially. Once local frequent itemsets are found, the entire dataset is scanned again to find global frequent items sets. From these frequent global frequent items, Closed frequents itemsets are mined .


### Implementation
1) For each partition, algorithm scans all transactions to count number of occurences of each item. The items with count less than minimum support are discarded. 
2) From frequent 1-itemsets, 2-items sets are computed by 
finding combiantions of all items. Algorithm scans all transactions again to count all occurences of each 2-item.
The items with count less than minimum support are discarded as done above.
3) Step 2 is repeated till there are no k-items sets with count atleast equal to min support. Then k-1-item sets are returned. These are closed frequent items for each partition.
4) Once all local frequent item sets are computed, global frequent itemsets are found by scanning entire dataset again.
