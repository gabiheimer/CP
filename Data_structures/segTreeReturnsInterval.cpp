#include<bits/stdc++.h>
#define ll long long int

using namespace std;

struct Node{
	ll maxDif; // stores the maximum difference between adjacent numbers in an interval
	ll hLeft;
	ll hRight;
	ll qtt;
};

const int maxn = 100005;
vector<Node> tree(4*maxn);

void update(ll pos, ll i, ll j, ll x, ll val){
	ll esq = 2*pos;
	ll dir = 2*pos + 1;
	ll mid = (i+j)/2;
	
	if(i == j){
		tree[pos].maxDif = 0;
		tree[pos].hLeft = val;
		tree[pos].hRight = val;
		tree[pos].qtt = 1;
	} else {
		if(x <= mid) update(esq, i, mid, x, val);
		else update(dir, mid+1, j, x, val);
		
		tree[pos].hLeft = tree[esq].hLeft;
		tree[pos].hRight = tree[dir].hRight;
		
		tree[pos].maxDif = max(max(tree[esq].maxDif, tree[dir].maxDif), abs(tree[esq].hRight - tree[dir].hLeft));
		
		tree[pos].qtt = tree[esq].qtt + tree[dir].qtt;
	}
}

pair<ll, pair<bool,bool>> reverseQuery(ll pos, ll i, ll j, ll maxD, ll inPos){
    // this query returns the amount of elements in an interval according to a rule
    // in this case, it returns the amount of consecutive elements which contain
    // inPos and where the difference between them is <= maxD
    // pair<ll,pair<bool,bool>> == {qtt, canLooktoLeft, canLooktoRight}

    ll esq = 2*pos;
	ll dir = 2*pos + 1;
	ll mid = (i+j)/2;
	
	if(tree[pos].maxDif > maxD){
        // if the whole interval doesn't follow the rule
		pair<ll,pair<bool,bool>> e ={0,{false,false}}, d = {0,{false,false}};

		if(inPos <= mid){
            // if the initial position is to the left of this node
            // we will search in the left side
			e = reverseQuery(esq,i,mid,maxD,inPos);
			
            // if we can still look to the right we will
			if(e.second.second && abs(tree[esq].hRight - tree[dir].hLeft) <= maxD){
				d = reverseQuery(dir, mid+1,j,maxD,inPos);
			}
		} else {
            // if the initial position is to the right of this node
            // we will search in the right side
			d = reverseQuery(dir, mid+1,j,maxD,inPos);
			
            // if we can still look to the left we will
			if(d.second.first && abs(tree[esq].hRight - tree[dir].hLeft) <= maxD){
				e = reverseQuery(esq,i,mid,maxD,inPos);
			}
		}
		
        // if both left and right sides don't follow the rule, we return
        // that we can't look to the left or right anymore

        // if only the left side follows the rule, we return that
        // we can't look to the right anymore and the 'canLooktoLeft'
        // will be the same as the return from the left search

        // if only the right side follows the rule, we return that
        // we can't look to the left anymore and the 'canLooktoRight'
        // will be the same as the return from the right search

        // if both sides follow the rule, the 'canLooktoLeft' will be
        // equal to the return from the left search and the 'canLooktoRight'
        // will be equal to the return from the right search

		if(d.first == 0 && e.first == 0) return {0,{false,false}};
		else if(d.first == 0) return {e.first,{e.second.first,false}};
		else if(e.first == 0) return {d.first,{false,d.second.second}};
		else return {e.first+d.first, {e.second.first,d.second.second}};
		
	} else {
		return {tree[pos].qtt, {true,true}};
	}
}