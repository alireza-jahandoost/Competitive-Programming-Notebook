// Returns intersection of 2 rectangles in O(1)
// you have to specify MAX_CORD and MIN_CORD
// represanting the maximum and minimum cordinate
// that a point can have

const int MAX_CORD = 500;
const int MIN_CORD = -500;

struct point{
	int x;
	int y;
};

struct rect{
	point topLeft;
	point bottomRight;

	long long area(){
		return ((long long) bottomRight.x - topLeft.x) *
			(bottomRight.y - topLeft.y);
	}
};

rect intersection(rect a, rect b){
	rect c = {MAX_CORD, MAX_CORD, MIN_CORD, MIN_CORD};
	c.topLeft.x = max(a.topLeft.x, b.topLeft.x);
	c.topLeft.y = max(a.topLeft.y, b.topLeft.y);
	c.bottomRight.x = min(a.bottomRight.x, b.bottomRight.x);
	c.bottomRight.y = min(a.bottomRight.y, b.bottomRight.y);

	return c;
}
