// zero indexed
// init(n): initial a segment tree with size n
// build(vector<int>): build segment tree by the given array
// modify(l, r, v): modify elements from l to r by v
// calc(l, r): returns calculation of [l,r)

// condition: (a OP1 v) OP2 (b OP1 v) = (a OP2 b) OP 1
// example: (a + v) min (b + v) = (a min b) + v
// modify: OP1		calc: OP2

// NEEDS_CHANGE
struct valueItem{
	char start, end;
	int seg;
	int length;
	bool operator==(valueItem b){
		return start == b.start &&
			end == b.end &&
			length == b.length &&
			seg == b.seg;
	}
};

struct operationItem{
	char color;
};
// END_NEEDS_CHANGE

struct segtree{
	int size;
	vector<operationItem> operations;
	vector<valueItem> values;
	// NEEDS_CHANGE
	const operationItem INITIAL_OPERATION_VALUE = {'0'};
	const valueItem INITIAL_VALUES_VALUE = {'W','W',0,0};
	const operationItem NO_OPERATION = {'0'};
	const valueItem NEUTRAL_ELEMENT = {'0','0',0,0};

	operationItem modify_op(operationItem a, operationItem b, long long len){
		if(b.color == NO_OPERATION.color) return a;
		return b;
	}

	valueItem modify_op(valueItem a, operationItem b, long long len){
		if(b.color == NO_OPERATION.color) return a;
		return {b.color, b.color, b.color == 'W' ? 0 : 1, b.color == 'W' ? 0 : (int)len};
	}

	valueItem calc_op(valueItem a, valueItem b){
		if(a == NEUTRAL_ELEMENT) return b;
		if(b == NEUTRAL_ELEMENT) return a;
		valueItem c;
		c.start = a.start;
		c.end = b.end;
		c.seg = a.seg + b.seg;
		c.length = a.length + b.length;
		if(a.end == b.start && a.end == 'B') c.seg --;
		return c;
	}

	valueItem single(int value){
		// some assignments here
		return {char(value),char(value),1};
	}
	// END_NEEDS_CHANGE

	void apply_modify(operationItem &a, operationItem b, long long len){
		a = modify_op(a,b,len);
	}

	void apply_modify(valueItem &a, operationItem b, long long len){
		a = modify_op(a,b,len);
	}

	void apply_calc(valueItem &a, valueItem b){
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

	void build(vector<long long>&a, int x, int lx, int rx){
		if(rx - lx == 1){
			if(lx < (int)a.size())
				values[x] = single(a[lx]);
			return;
		}

		int m = (lx + rx) / 2;
		build(a, 2*x+1, lx, m);
		build(a, 2*x+2, m, rx);
		values[x] = calc_op(values[x*2+1], values[x*2+2]);
	}

	void build(vector<long long>&a){
		build(a, 0, 0, size);
	}
 
	void modify(int l, int r, operationItem v, int x, int lx, int rx){
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
 
	void modify(int l, int r, operationItem v){
		modify(l,r,v,0,0,size);
	}
 
	valueItem calc(int l, int r, int x, int lx, int rx){
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
 
	valueItem calc(int l, int r){
		return calc(l,r,0,0,size);
	}
};
