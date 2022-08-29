// add(value): adds value to minimum queue and maximum queue
// remove(value): remove value from queues
// getMinimum(): returns minimum of segment
// getMaximum(): returns maximum of segment

template <typename MinMaxType>
struct MinMaxQueue{
	deque<MinMaxType>minimum, maximum;

	void add(MinMaxType value){
		// add to minimum
		while(!minimum.empty() && minimum.back() > value)
			minimum.pop_back();
		minimum.push_back(value);

		// add to maximum
		while(!maximum.empty() && maximum.back() < value)
			maximum.pop_back();
		maximum.push_back(value);
	}

	void remove(MinMaxType value){
		// remove from minimum
		if(!minimum.empty() && minimum.front() == value)
			minimum.pop_front();

		// remove from maximum
		if(!maximum.empty() && maximum.front() == value)
			maximum.pop_front();
	}

	MinMaxType getMaximum(){
		return maximum.front();
	}

	MinMaxType getMinimum(){
		return minimum.front();
	}
};
