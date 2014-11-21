#include<string>
#include<functional>
namespace tiny
{
class calculate_error:public std::runtime_error
{
	calculate_error(const std::string& msg):runtime_error(msg){}
};

template<typename T> class calculator
{
private:
	enum class precedence
	{
		NONE, OR, XOR, AND, SHIFI, PLUS, MUL, POWER
	};

	enum class associativity
	{
		LEFT, RIGHT
	};

	struct operation
	{
		operation(function<T(T,T)> op_ = [](T,T){return T(0)}, precedence pre_ = precedence::NONE, associativity assoc_ = associativity::LEFT)
		:op(op_), pre(pre_), assoc(assoc_)
		{
		}
		function<T(T,T)> op;
		precedence pre;
		associativity assoc;
	};

public:
	calculator(const std::string& expr):expr_(expr){}

	void unexpected(const string& expect = "")
	{
		std::stringstream ss;
		ss << "unexpected token at" << index_-expr_.begin() << ": " << std::string(index_, expr_.end()) << std::endl;
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
		auto beg = index_;	
		index_ = std::find_if_not(beg, end_, std::isdigit)
		string number = string(beg, index_);
		if(typeid(T))
	}
	T read_number()
	{
		skip_space();
		if(is_end())
			throw calculate_error("expected a number in the end of the expr");
		char ch = get_char(); 
		if(std::isdigit(ch))
			return parse_number();
		else if(ch == '-')
			return -read_number();
		else if(ch == '~')
			return ~read_number();
		else if(ch == '(')
		{
			++index_;
			T value = eval();
			if(get_char() != ')')
				unexpected(")");
			++index_;
			return value;
		}
		else
			unexpected("number");
	}

	T eval()
	{
		ops_.add(operation());
		T value = read_number();
		while(!ops_.empty())
		{
			operation op = read_op();
			while(op.pre<ops_.top().pre || (op.pre==ops_.top().pre && ops_.top().assoc==associativity::LEFT))
			{
				if(ops_.top().pre == precedence::NONE)
					return value;
				value = op.op(data_.top(), value);
				op.pop();
				value.pop();
			}
			ops_.push(op);
			data_.push(value);
		}
	}
private:
	const std::string expr_;
	auto index_ = expr_.begin();
	const auto end_ = expr_.end();
	std::stack<operation> ops_;
	std::stack<T> data_;
	std::map<std::string, operation> ma=
	{
		{"**", {[](T a, T b){return std::pow(a,b);}, precedence::POWER, associativity::RIGHT}},
		{"*", {std::multiplies<T,T>(), precedence::MUL}},
		{"/", {std::divides<T,T>(), precedence::MUL}},
		{"%", {std::modulus<T,T>(), precedence::MUL}},
		{"+", {std::plus<T,T>(), precedence::PLUS}},
		{"-", {std::minus<T,T>(), precedence::PLUS}},
		{"<<", {[](T a, T b){return a<<b;}, precedence::SHIFT}},
		{">>", {[](T a, T b){return a>>b;}, precedence::SHIFT}},
		{"&", {[](T a, T b){return a&b;}, precedence::AND}},
		{"^", {[](T a, T b){return a^b;}, precedence::XOR}},
		{"|", {[](T a, T b){return a|b;}, precedence::OR}},
	}
};
}
