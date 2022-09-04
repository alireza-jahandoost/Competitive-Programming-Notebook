// condition: f(a,a) = a
// build(vector): will build the st
// get(l, r): will return from l to r

template <typename SparseTableType>
struct SparseTable{
	const int K = 28;
	vector<vector<SparseTableType>> st;
	vector<int> lg;
	int size;

	// NEEDS_CHANGE
	SparseTableType f(SparseTableType a, SparseTableType b){
		return min(a,b);
	}
	// END_NEEDS_CHANGE

	void build(vector<SparseTableType>& a){
		size = a.size() + 100;

		lg.resize(size);
		lg[1] = 0;
		for (int i = 2; i < size; i++)
		    lg[i] = lg[i/2] + 1;

		st.resize(size, vector<SparseTableType>(K));

		for (int i = 0; i < size; i++)
		    st[i][0] = a[i];

		for (int j = 1; j <= K; j++)
		    for (int i = 0; i + (1 << j) <= size; i++)
			st[i][j] = f(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
	}

	SparseTableType get(int L, int R){
		int j = lg[R - L + 1];
		return f(st[L][j], st[R - (1 << j) + 1][j]);
	}

};
