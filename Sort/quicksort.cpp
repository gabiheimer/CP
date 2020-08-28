// idea:
// index l to i will contain nums < pivot
// index i+1 to r-1 will contain nums >= pivot
// pivot = nums[r]
int partition(int l, int r, vector<int> &nums) {
    int i = l-1;
    
    for(int j = l; j < r; j++) {
        if(nums[j] < nums[r]) {
            i++;
            swap(nums[j], nums[i]);
        }
    }
    
    swap(nums[r], nums[i+1]);
    return i+1;
}

void quicksort(int l, int r, vector<int> &nums) {
    if(l >= r) return;
    
    int pIndex = partition(l, r, nums);
    
    quicksort(l, pIndex-1, nums);
    quicksort(pIndex+1, r, nums);
}