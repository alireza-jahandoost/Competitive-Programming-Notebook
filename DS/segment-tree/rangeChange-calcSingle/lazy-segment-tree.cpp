// zero indexed
// init(n): initial a segment tree with size n
// build(vector<int>): build segment tree by the given array
// modify(l, r, v): modify elements from l to r by v
// get(i): returns item i

// NEEDS_CHANGE
struct operationItem{
	long long minimum, maximum;
	int operation;
	bool operator==(operationItem b){
		return minimum == b.minimum && maximum == b.maximum;
	}
};
// END_NEEDS_CHANGE

struct segtree{
	int size;
	vector<operationItem> operations;
	// NEEDS_CHANGE
	const operationItem NO_OPERATION = {0, INT_MAX, 0};
 
	operationItem operation(operationItem a, operationItem b){
		if(a.operation == 0) return b;
		if(b.operation == 0) return a;
		if(b.operation == 1){
			a.minimum = min(a.minimum, b.maximum);
			a.maximum = min(a.maximum, b.maximum);
			a.minimum = max(a.minimum, b.minimum);
			a.maximum = max(a.maximum, b.minimum);
			a.operation = 1;
		}else{
			a.minimum = max(a.minimum, b.minimum);
			a.maximum = max(a.maximum, b.minimum);
			a.minimum = min(a.minimum, b.maximum);
			a.maximum = min(a.maximum, b.maximum);
			a.operation = 2;
		}
		return a;
	}
	// END_NEEDS_CHANGE
 
	void apply_operation(operationItem &a, operationItem b){
		a = operation(a,b);
	}
 
	void propagate(int x, int lx, int rx){
		if(rx - lx == 1){
			return;
		}
		apply_operation(operations[2*x+1], operations[x]);
		apply_operation(operations[2*x+2], operations[x]);
		operations[x] = NO_OPERATION;
	}
 
	void init(int n){
		size = 1;
		while(size < n) size *= 2;
		operations.resize(size*2, NO_OPERATION);
	}
 
	void modify(int l, int r, operationItem v, int x, int lx, int rx){
		propagate(x, lx, rx);
		if(r <= lx || l >= rx){
			return;
		}
 
		if(r >= rx && l <= lx){
			operations[x] = operation(operations[x], v);
			return;
		}
 
		int m = (lx + rx) / 2;
 
		modify(l,r,v,2*x+1,lx,m);
		modify(l,r,v,2*x+2,m,rx);
	}
 
	void modify(int l, int r, operationItem v){
		modify(l,r,v,0,0,size);
	}
 
	operationItem get(int i, int x, int lx, int rx){
		propagate(x, lx, rx);
		if(rx - lx == 1){
			return operations[x];
		}
 
		int m = (lx + rx) / 2;
 
		if(m > i) return get(i, 2*x+1, lx, m);
		else return get(i, 2*x+2, m, rx);
	}
 
	operationItem get(int i){
		return get(i,0,0,size);
	}
};
