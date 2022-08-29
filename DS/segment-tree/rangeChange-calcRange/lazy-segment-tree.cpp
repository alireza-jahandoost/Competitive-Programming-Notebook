// zero indexed
// init(n): initial a segment tree with size n
// build(vector<int>): build segment tree by the given array
// modify(l, r, v): modify elements from l to r by v
// calc(l, r): returns calculation of [l,r)

// condition: (a OP1 v) OP2 (b OP1 v) = (a OP2 b) OP 1
// example: (a + v) min (b + v) = (a min b) + v
// modify: OP1		calc: OP2

template <typename SegmentType>
struct segtree{
	int size;
	vector<SegmentType> operations;
	vector<SegmentType> values;
	// NEEDS_CHANGE
	const SegmentType INITIAL_OPERATION_VALUE = 0;
	const SegmentType INITIAL_VALUES_VALUE = 0;
	const SegmentType NO_OPERATION = 0;
	const SegmentType NEUTRAL_ELEMENT = LLONG_MAX;

	SegmentType modify_op(SegmentType a, SegmentType b, long long len){
		return a + b;
	}

	SegmentType calc_op(SegmentType a, SegmentType b){
		return min(a,b);
	}
	// END_NEEDS_CHANGE

	void apply_modify(SegmentType &a, SegmentType b, long long len){
		a = modify_op(a,b,len);
	}

	void apply_calc(SegmentType &a, SegmentType b){
		a = calc_op(a,b);
	}

	void init(int n){
		size = 1;
		while(size < n) size *= 2;
		operations.resize(size*2, INITIAL_OPERATION_VALUE);
		values.resize(size*2, INITIAL_VALUES_VALUE);
	}

	void propagate(int x, int lx, int rx){
		if(rx - lx == 1) return;
		apply_modify(operations[2*x+1], operations[x], 1);
		apply_modify(operations[2*x+2], operations[x], 1);
		int m = (lx + rx) / 2;
		apply_modify(values[2*x+1], operations[x], m - lx);
		apply_modify(values[2*x+2], operations[x], rx - m);
		operations[x] = NO_OPERATION;
	}

	void build(vector<SegmentType>&a, int x, int lx, int rx){
		if(rx - lx == 1){
			if(lx < (int)a.size())
				values[x] = a[lx];
			return;
		}

		int m = (lx + rx) / 2;
		build(a, 2*x+1, lx, m);
		build(a, 2*x+2, m, rx);
		values[x] = calc_op(values[x*2+1], values[x*2+2]);
	}

	void build(vector<SegmentType>&a){
		build(a, 0, 0, size);
	}

	void modify(int l, int r, SegmentType v, int x, int lx, int rx){
		propagate(x, lx, rx);
		if(r <= lx || l >= rx){
			return;
		}

		if(r >= rx && l <= lx){
			apply_modify(operations[x], v, 1);
			apply_modify(values[x], v, rx - lx);
			return;
		}

		int m = (lx + rx) / 2;

		modify(l,r,v,2*x+1,lx,m);
		modify(l,r,v,2*x+2,m,rx);

		values[x] = calc_op(values[2*x+1], values[2*x+2]);
	}

	void modify(int l, int r, SegmentType v){
		modify(l,r,v,0,0,size);
	}

	SegmentType calc(int l, int r, int x, int lx, int rx){
		propagate(x, lx, rx);
		if(r <= lx || l >= rx){
			return NEUTRAL_ELEMENT;
		}

		if(r >= rx && l <= lx){
			return values[x];
		}

		int m = (lx + rx) / 2;

		auto first = calc(l,r,2*x+1,lx,m);
		auto second = calc(l,r,2*x+2,m,rx);

		return calc_op(first, second);
	}

	SegmentType calc(int l, int r){
		return calc(l,r,0,0,size);
	}
};
