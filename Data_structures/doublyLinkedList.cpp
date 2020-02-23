#include<bits/stdc++.h>

using namespace std;

struct Node{
    int val;
    Node* next;
    Node* prev;

    Node(int v){
        this->val = v;
        this->next = NULL;
        this->prev = NULL;
    }
};

class Dlist{
    Node* head;
    Node* tail;

    public:
    Dlist(){
        // sentinela no comeco e final
        Node* aux1 = new Node(-1);
        Node* aux2 = new Node(-1);

        this->head = aux1;
        this->tail = aux2;

        this->head->next = this->tail;
        this->tail->prev = this->head;
    }

    void pushBack(int v){
        Node* aux = new Node(v);
        Node* last = this->tail->prev;

        last->next = aux;
        aux->prev = last;
        aux->next = tail;
        tail->prev = aux;
    }

    // insere pra o valor ficar na posicao indicada
    void insertByPos(int v, int pos){
        Node* before = head;
        while(pos--) before = before->next;
        Node* after = before->next;

        Node* aux = new Node(v);

        aux->prev = before;
        before->next = aux;

        aux->next = after;
        after->prev = aux;
    }

    // remove valor da posicao indicada
    void rmvByPos(int pos){
        Node* before = head;
        while(pos--) before = before->next;
        Node* after = before->next->next;

        before->next = after;
        after->prev = before;
    }

    // remove valores no range [l,r]
    void rmvRange(int l, int r){
        Node* before;
        Node* after = head;

        for(int i = 0; i < r; i++){
            if(i == l) before = after;
            after = after->next;
        }
        after = after->next->next;

        before->next = after;
        after->prev = before;
    }

    // funcoes pra debugar
    void print(){
		Node* cur = head->next;
		while(cur->val != -1){
			cout << cur->val << " ";
			cur = cur->next;
		}
		cout << endl;
	}
	
	void reversePrint(){
		Node* cur = tail->prev;
		while(cur->val != -1){
			cout << cur->val << " ";
			cur = cur->prev;
		}
		cout << endl;
	}
};