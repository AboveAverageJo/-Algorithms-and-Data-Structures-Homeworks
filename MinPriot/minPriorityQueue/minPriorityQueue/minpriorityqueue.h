#pragma once

#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of elements in the MinPriorityQueue.
	//
	// Assume that the operations of unordered_map are O(1) time 
	// (they are average case, but not worst-case).

public:
	// Creates an empty MinPriorityQueue
	MinPriorityQueue()
	{
		// TODO
		
		
	}

	// Returns the number of elements in the MinPriorityQueue.
	//
	// Must run in O(1) time.
	int size()
	{
		// TODO	
		return H.size();
	}

	// Pushes a new value x with priority p
	// into the MinPriorityQueue.
	//
	// Must run in O(log(n)) time.		 
 	void push(T x, int p)
	{
		//pushes back the pair
		H.push_back(pair<T,int>(x, p));
		I.insert(pair<T, int>(x, H.size() - 1));
		bubbleUp(H.size() - 1);
		
	}

	void bubbleUp(int x)
	{
		int c =x;
		while (c != 0)
		{
			//parent index
			int parent = (c - 1) / 2;
			//comparing with parent
			if (H[c].second < H[parent].second)
			{
				swap(H[c], H[parent]);
				swap(I[H[c].first], I[H[parent].first]);
			}
			else if (H[c].second > H[parent].second)
			{
				return;
			}

			c = parent;
		}
	}

	// Returns the value at the front of the MinPriorityQueue.
	// Undefined behavior if the MinPriorityQueue is empty.
	// 
	// Must run in O(1) time.
	T front()
	{
		// TODO	
		return H[0].first;

	}

	// Removes the value at the front of the MinPriorityQueue.
	// Undefined behavior if the MinPriorityQueue is empty.
	//
	// Must run in O(log(n)) time. 
	void pop()
	{
		if (H.size() == 0)
		{
			return;
		}
		else if (H.size() == 1)
		{
			H.pop_back();
			return;
		}
		else
		{
			swap(H[0], H[size() - 1]);
			H.pop_back();
			bubbleDown();
		}
	}

	void bubbleDown()
	{
		//current starts at index 0 because it gets the last one and puts it at the top
		int c = 0;
		//getting index of the smallest child
		int SC = smallestChild(c);

		//keeps looping until smallest child has no more children
		while (SC > 0)
		{
			
				
			//swap if the smallest child is less than the current
			if (H[SC].second < H[c].second)
			{
				swap(H[SC], H[c]);
				swap(I[H[SC].first], I[H[c].first]);
				//updating current to the smallest child because it just switched 
				c = SC;
			}
			//stop if the current is no longer bigger than the smallest child, return
			else if (H[c].second < H[SC].second)
			{
				return;
			}
			else if (H[c].second == H[SC].second)
			{
				return;
			}
			//geting new SC with the current index
			SC = smallestChild(c);
		}
	}

	int smallestChild(int x)
	{
		//getting index of left and right children
		unsigned int left = (2 * x + 1);
		unsigned int right = (2 * x + 2);

		//case if no children returns -1
		if (left > (H.size() - 1) && right > (H.size() - 1))
		return -1;
		//case when there's only one child
		if (right > (H.size()- 1))
			return left;
		//case when the left is the smallest child
		if (H[left].second < H[right].second)
			return left;
		//case when right is the smallest child
		if (H[right].second < H[left].second)
			return right;
		else
			return right;
	}

	// If x is in the MinPriorityQueue 
	// with current priority at least new_p,  
	// then changes the priority of x to new_p.
	// Undefined behavior otherwise.
	//
	// Must run in O(log(n)) time. 
	void decrease_key(T x, int new_p)
	{
		int index = I.at(x);
		H[index].second = new_p;
		bubbleUp(index);

	}




private:
	// You don't need any other instance variables,
	// but you can add some if you want to.
	vector< pair<T, int> > H; // The heap.
	unordered_map<T, int> I;  // Maps values to their indices in H.
};

#endif 

