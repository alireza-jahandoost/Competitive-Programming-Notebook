// init(r,c): inital the prefix array with r+1 rows (0 .. r) and c+1 columns (0 .. c)
// build(vector<vector<int>>): build prefix sum array
// get(): get the sum of rectangle ( all points inclusive )

struct prefix2D{
	int rows;
	int cols;
	vector<vector<long long>>values;

	void init(int r, int c){
		rows = r + 1;
		cols = c + 1;
		values.resize(rows + 1, vector<long long>(cols + 1));
	}

	// x1,y1      x1,y2
	// x2,y1      x2,y2

	// O(1)
	long long get(int x1, int y1, int x2, int y2){
		long long res = values[x2][y2];
		if(x1>0) res -= values[x1 - 1][y2];
		if(y1>0) res -= values[x2][y1 - 1];
		if(x1>0 && y1>0) res += values[x1 - 1][y1 - 1];
		return res;
	}

	// O(n^2)
	void build(vector<vector<int>> nums){
		for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++){
				values[i][j] = 
					(i > 0 ? values[i-1][j] : 0) + 
					(j > 0 ? values[i][j-1] : 0 ) - 
					(i > 0 && j > 0 ? values[i-1][j-1] : 0);
				if(i < (int)nums.size() && j < (int)nums[0].size())
					values[i][j] += nums[i][j];
			}
	}
};
