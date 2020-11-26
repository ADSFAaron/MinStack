// Design a stack that supports push, pop, top, and retrieving the minimum element

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// stack class template definition
template< typename T >
class MinStack
{
public:
	using iterator = T*;

	// Constructor; Constructs a zero Stack with size n
	MinStack(unsigned int n = 0);

	// Destroys Stack
	~MinStack();

	// Returns the number of elements in the Stack
	unsigned int size() const;

	// Push one Element to stack
	void push(T&);

	// Pop one Element from stack
	void pop();

	// Return the last Element from stack
	T top();

	// Return the smallest elements from stack
	T getMin();

	void printStack();

	bool empty();

private:
	T* myFirst = nullptr;
	T* myLast = nullptr;
	unsigned int Size;
}; // end class template vector


template <typename T>
MinStack<T>::MinStack(const unsigned int n)
	:Size(n)
{
	if (n > 0)
	{
		myFirst = new T[n]();
		myLast = myFirst + n;
	}

}

template <typename T>
MinStack<T>::~MinStack()
{
	if (myFirst != nullptr)
	{
		delete[] myFirst;
	}

	myLast = nullptr;

}

template <typename T>
unsigned int MinStack<T>::size() const
{
	return Size;
}

template <typename T>
void MinStack<T>::push(T& val)
{
	// Create a new Space
	//T* tmp = new T[Size + 1]();
	T* tmp_iter = myFirst;
	T* tmp_begin_iter = myFirst;
	T* tmp_end_iter = myLast;

	++Size;
	myFirst = new T[Size]();
	myLast = myFirst + Size;
	T* ori_iter = myFirst;

	for (; tmp_iter != tmp_end_iter; ++ori_iter, ++tmp_iter)
	{
		*ori_iter = *tmp_iter;
	}

	*ori_iter = val;


	// delete original stack
	if (tmp_begin_iter != nullptr)
		delete[] tmp_begin_iter;
}

template <typename T>
void MinStack<T>::pop()
{
	// Determine stack in null or not
	if (!empty())
	{
		T* tmp_iter = myLast;
		--myLast;
		--tmp_iter;

		// Remove elements
		tmp_iter = nullptr;

		--Size;
	}
}

template <typename T>
T MinStack<T>::top()
{
	if (!empty())
	{
		T* tmp = myLast;
		return *(--tmp);
	}
	else
	{
		return NULL;
	}
}

template <typename T>
T MinStack<T>::getMin()
{
	T* tmp = new T();

	// Copy origin stack
	T* saveStack = new T[Size]();
	T* tmp3_ptr = saveStack;		// save the last element address

	for (T* tmp_ptr = myFirst; tmp_ptr != myLast; ++tmp_ptr, ++tmp3_ptr)
	{
		*tmp3_ptr = *tmp_ptr;
	}

	// Sorting
	for (T* tmp_ptr = saveStack; tmp_ptr != tmp3_ptr; ++tmp_ptr)
	{
		for (T* tmp2_ptr = tmp_ptr; tmp2_ptr != tmp3_ptr; ++tmp2_ptr)
		{
			if (*tmp_ptr > *tmp2_ptr)
			{
				*tmp = *tmp_ptr;
				*tmp_ptr = *tmp2_ptr;
				*tmp2_ptr = *tmp;
			}
		}
	}

	/*T* itera = saveStack;
	for (; itera != tmp3_ptr; ++itera)
	{
		cout << *itera << " ";
	}

	cout << endl;*/

	delete tmp;

	return *saveStack;
}

template <typename T>
void MinStack<T>::printStack()
{
	T* iter = myFirst;
	for (; iter != myLast; ++iter)
	{
		cout << *iter << " ";
	}

	cout << endl;
}

template <typename T>
bool MinStack<T>::empty()
{
	if (Size == 0 && myFirst == myLast)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void reverse_Str(string& in)
{
	for (int i = 0; i < in.size() / 2; ++i)
	{
		swap(in[i], in[in.size() - i - 1]);
	}
}

void implement(vector<string>& instruction, vector<string>& instruction_val, vector<string>& output)
{
	string keyWord[] = { "MinStack","push","getMin","pop","top" };
	MinStack<int> min_stack;
	for (int i = 0; i < instruction.size(); ++i)
	{
		if (instruction[i] == keyWord[0])
		{
			// Create a stack called min_stack
			output.push_back("null");
		}
		else if (instruction[i] == keyWord[1])
		{
			// push a value into min_stack
			int tmp = stoi(instruction_val[i]);
			min_stack.push(tmp);

			output.push_back("null");
		}
		else if (instruction[i] == keyWord[2])
		{
			// get the smallest value
			output.push_back(std::to_string(min_stack.getMin()));
		}
		else if (instruction[i] == keyWord[3])
		{
			// pop a value from min_stack
			min_stack.pop();
			output.push_back("null");
		}
		else if (instruction[i] == keyWord[4])
		{
			// getthe top value of min_stack
			output.push_back(std::to_string(min_stack.top()));
		}

	}
}

// Main Function
int main()
{
	string input;
	vector<string> instruction;
	vector<string> instruction_value;
	vector<string> instruction_output;
	MinStack<string> buffer;
	bool quote = false;

	cin >> input;

	// Split "" Instruction
	stringstream ss(input);

	while (getline(ss, input, '\"'))
	{
		if (quote)
		{
			// instruction
			quote = false;

			instruction.push_back(input);
		}
		else
		{
			// other symbol
			quote = true;
		}
	}

	// split instruction value

	cin >> input;
	ss << input;

	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == ']')
		{
			string tmp, tmp2;

			while ((tmp2 = buffer.top()) != "[")
			{
				tmp += tmp2;
				buffer.pop();
			}

			buffer.pop();
			reverse_Str(tmp);
			instruction_value.push_back(tmp);
		}
		else if (input[i] == ',')
		{

		}
		else
		{
			string tmp;
			tmp = input[i];
			buffer.push(tmp);
		}
	}

	/*for (int i = 0; i < instruction.size(); ++i)
	{
		cout << instruction[i] << "  " << instruction_value[i] << endl;
	}*/

	implement(instruction, instruction_value, instruction_output);

	cout << "[";
	for (int i = 0; i < instruction_output.size(); ++i)
	{
		cout << instruction_output[i] << ",";
	}

	cout << "]" << endl;

	system("pause");
	return 0;
}
