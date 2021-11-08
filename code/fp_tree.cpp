#include<bits/stdc++.h>
using namespace std;
class Node{
public:int item_number;
       int count;
       Node* next_link;
       map<int,Node*>children;
       Node(int val){
            item_number=val;
            count=0;
            next_link=NULL;
       }
};
class FP_TREE {
    vector<int> transactions[59601];
    Node *root;
    map<int, int> item_set;
    vector<int> item_set_freq;
    map<int, Node *> item_header;
    int support_count;
    int transactions_size;

public:
    FP_TREE(int s_count) {
        root = new Node(-1);
        support_count = s_count;
        transactions_size = 0;
    }

    void read_dataset(string file_name) {
        cout << "READING DATASET....." << endl;
        ifstream read_file(file_name);
        map<int, int> temp_item_set;
        vector<int> temp_transactions[59601];
        string line;
        int index = 0;
        while (getline(read_file, line)) {
            stringstream ss(line);
            string token;
            while (getline(ss, token, ' ')) {
                if (stoi(token) != -1 && stoi(token) != -2) {
                    temp_item_set[stoi(token)]++;
                    temp_transactions[index].push_back(stoi(token));

                }

            }

            index++;
        }
        cout << "REMOVING ITEMS WITHOUT MINIMUM SUPPORT COUNT..." << endl;
        for (auto ele: temp_item_set) {
            if (ele.second >= support_count) {
                item_set.insert(ele);
            }
        }
        index = 0;
        bool flag;
        for (auto ele: temp_transactions) {
            flag = false;
            for (auto e: ele) {
                if (item_set.count(e)) {
                    flag = true;
                    transactions[index].push_back(e);
                }
            }
            sort(transactions[index].begin(), transactions[index].end());
            if (flag) {
                index++;
            }
        }
        transactions_size = index;
        cout << "COMPLETED READING....ITEM COUNT IS " << item_set.size() << " TRANSACTION SIZE IS " << transactions_size
             << endl;
        read_file.close();
    }

    void sort_transactions() {
        cout << "SORTING THE ITEMSET ACCORDING TO THEIR FREQUENCY" << endl;
        vector<pair<int, int>> temp_itemset;
        for (auto ele: item_set) {
            temp_itemset.push_back({ele.second, ele.first});
        }
        sort(temp_itemset.begin(), temp_itemset.end());
        for (auto ele: temp_itemset) {
            item_set_freq.push_back(ele.second);
            item_header[ele.second] = NULL;
        }
        reverse(item_set_freq.begin(), item_set_freq.end());
        cout << "SORTING THE TRANSACTIONS" << transactions_size << endl;
        for (int i = 0; i < transactions_size; i++) {

            vector<int> temp_vector;
            for (auto ele: item_set_freq) {
                if (binary_search(transactions[i].begin(), transactions[i].end(), ele)) {
                    temp_vector.push_back(ele);
                }
            }

            transactions[i] = temp_vector;

        }
    }

    Node *insert_item_list(Node *root, int index, int n, vector<int> &list) {
        root->count++;
        //base case
        if (index == n) {
            return root;
        }
        //check if present node as list[index[ as child
        int element = list[index];
        if (root->children.count(element)) {
            //element is present

            root->children[element] = insert_item_list(root->children[element], index + 1, n, list);
        } else {
            //create a new node with element as item number
            Node *new_node = new Node(element);
            //updating item header
            Node *head = item_header[element];
            if(head==NULL){
                head=new_node;
                head->next_link=NULL;
            }
            else{
                while (head->next_link != NULL) {
                    head = head->next_link;
                }
                head->next_link = new_node;
            }
            root->children[element] = insert_item_list(new_node, index + 1, n, list);
        }
        return root;
    }

    void construct_fp_tree() {
        cout << "CONSTRUCTING FP TREE";
        //parse the transactions
        for (int i = 0; i < transactions_size; i++) {
            root = insert_item_list(root, 0, transactions[i].size(), transactions[i]);
        }
    }
};
int main(){
    FP_TREE fp(100);
    fp.read_dataset("dataset.txt");
    fp.sort_transactions();
    fp.construct_fp_tree();


    return 0;
}