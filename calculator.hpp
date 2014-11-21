#include<iostream>
#include<string>
#include<cctype>
#include<map>
#include<stack>
#include<sstream>
#include<functional>
#include<algorithm>
using std::cout;
using std::endl;
namespace tiny
{
class calculate_error:public std::runtime_error
{
public:
	calculate_error(const std::string& msg):runtime_error(msg){}
};

template<typename T> class calculator
{
private:
	enum class precedence
	{
		NONE, OR, XOR, AND, SHIFT, PLUS, MUL, POWER
	};

	enum class associativity
	{
		LEFT, RIGHT
	};

	struct operation
	{
		operation(std::function<T(T,T)> op_ = [](T,T){return T(9999);}, precedence pre_ = precedence::NONE, associativity assoc_ = associativity::LEFT)
		:op(op_), pre(pre_), assoc(assoc_)
		{
		}
		std::function<T(T,T)> op;
		precedence pre;
		associativity assoc;
	};

public:
	calculator(const std::string& expr):expr_(expr){}

	void unexpected(const std::string& expect = "")
	{
		std::stringstream ss;
		ss << "unexpected token at " << index_-expr_.begin() << ": " << std::string(index_-1, expr_.end()) << std::endl;
		if(!expect.empty())
			ss << "expect: " << expect <<std::endl;
		throw calculate_error(ss.str());
	}

	char get_char()
	{
		return *index_;
	}

	T parse_number()
	{
		//using std::stoll;
		auto beg = index_;	
		index_ = std::find_if_not(beg, end_, [](char ch)
				{
				for(int i='0'; i!='9'; ++i)
				if(i==ch)
				return true;
				return false;
				});
		std::string number = string(beg, index_);
		if(typeid(T) == typeid(int))
			return std::stoi(number);
		else if(typeid(T) == typeid(long))
			return std::stol(number);
		else 
			return std::stoll(number);
	}

	void skip_space()
	{
		while(index_ != end_ && std::isspace(*index_))
			++index_;
	}

	bool is_end()
	{
		return index_ == end_;
	}

	T read_number()
	{
		skip_space();
		if(is_end())
			throw calculate_error("expected a number in the end of the expr");
		char ch = get_char(); 
		if(std::isdigit(ch))
			return parse_number();
		++index_;
		if(ch == '-')
			return -read_number();
		else if(ch == '~')
			return ~read_number();
		else if(ch == '(')
		{
			int old_num = ++left_backet_;
			T value = eval();
			if(left_backet_ == old_num)
				unexpected(")");
			return value;
		}
		else
			unexpected("number");
		return 0;//to supress warning
	}

	operation read_op()
	{
		skip_space();
		if(is_end())
			return operation();
		char ch = get_char();
		if(ch == '*' || ch == '<' || ch == '>')
		{
			if((++index_ != end_) && (get_char() == ch))
			{
				++index_;
				return (ma.find(ch*256+ch))->second;
			}
			else
				--index_;
		}
		++index_;
		auto it = ma.find(ch);
		if(it != ma.end())
			return it->second;
		else if(ch == ')' && left_backet_--)
			return operation();
		else
			unexpected("operation");
		return operation();//to supress warning
	} 

	T eval()
	{
		ops_.push(operation());
		T value = read_number();
		while(!ops_.empty())
		{
			operation op = read_op();
			while(op.pre<ops_.top().pre || (op.pre==ops_.top().pre && ops_.top().assoc==associativity::LEFT))
			{
				if(ops_.top().pre == precedence::NONE)
				{
					ops_.pop();
					return value;
				}
				value = ops_.top().op(data_.top(), value);
				ops_.pop();
				data_.pop();
			}
			ops_.push(op);
			data_.push(value);
			value = read_number();
		}
		return 0;//to supress warning
	}
private:
	const std::string expr_;
	std::string::const_iterator index_ = expr_.begin();
	const std::string::const_iterator end_ = expr_.end();
	std::stack<operation> ops_;
	std::stack<T> data_;
	int left_backet_ = 0;
	const std::map<int, operation> ma=
	{
		{'*'*256+'*',	 {[](T a, T b){return std::pow(a,b);}, precedence::POWER, associativity::RIGHT}},
		{'*',	 {std::multiplies<T>(), precedence::MUL}},
		{'/',	 {std::divides<T>(), precedence::MUL}},
		{'%',	 {std::modulus<T>(), precedence::MUL}},
		{'+',	 {std::plus<T>(), precedence::PLUS}},
		{'-',	 {std::minus<T>(), precedence::PLUS}},
		{'<'*256+'<',	 {[](T a, T b){return a<<b;}, precedence::SHIFT}},
		{'>'*256+'>',	 {[](T a, T b){return a>>b;}, precedence::SHIFT}},
		{'&',	 {[](T a, T b){return a&b;}, precedence::AND}},
		{'^',	 {[](T a, T b){return a^b;}, precedence::XOR}},
		{'|',	 {[](T a, T b){return a|b;}, precedence::OR}},
	};
};

template<typename T=int> T calculate(const std::string& expr)
{
	calculator<T> ca(expr);
	return ca.eval();
}
}
