// zero indexed
// init(n): initial a segment tree with size n
// build(vector<int>): build segment tree by the given array
// set(i, v): set index i equal to v
// calc(l, r): returns calculation of [l,r)

struct item{
	// NEEDS_CHANGE
	long long value;
	// END_NEEDS_CHANGE
};

struct segtree{
	int size;
	vector<item> values;

	// NEEDS_CHANGE
	item NEUTRAL_ELEMENT = {0};

	item merge(item a, item b){
		return {a.value + b.value};
	}

	item single(int value){
		return {value};
	}
	// END_NEEDS_CHANGE

	void init(int n){
		size = 1;
		while(size < n) size *= 2;
		values.resize(size*2);
	}

	void build(vector<int>& a, int x, int lx, int rx){
		if(rx - lx == 1){
			if(lx < (int)a.size()){
				values[x] = single(a[lx]);
			}
			return;
		}
		int m = (lx + rx) / 2;
		build(a, 2*x+1, lx, m);
		build(a, 2*x+2, m, rx);
		values[x] = merge(values[2*x+1], values[2*x+2]);
	}

	void build(vector<int>& a){
		build(a, 0, 0, size);
	}

	void set(int i, int v, int x, int lx, int rx){
		if(rx - lx == 1){
			values[x] = single(v);
			return;
		}

		int m = (lx + rx) / 2;
		if(i < m)
			set(i, v, 2*x+1, lx, m);
		else
			set(i, v, 2*x+2, m, rx);

		values[x] = merge(values[2*x+1], values[2*x+2]);
	}

	void set(int i, int v){
		set(i,v,0,0,size);
	}

	item calc(int l, int r, int x, int lx, int rx){
		if(r <= lx || l >= rx){
			return NEUTRAL_ELEMENT;
		}

		if(r >= rx && l <= lx){
			return values[x];
		}

		int m = (lx + rx) / 2;
		return merge(calc(l,r,2*x+1,lx,m), calc(l,r,2*x+2,m,rx));
	}

	item calc(int l, int r){
		return calc(l,r,0,0,size);
	}
};
