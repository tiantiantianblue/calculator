#ifndef BIGINT_H
#define BIGINT_H

#include<vector>
#include<string>
#include<iosfwd>
namespace tiny
{
	class bigint
	{
	public:
		bigint(int x=0);
		bigint(long x);
		bigint(long long x);
		bigint(const std::string& s);
		bigint(const char* s);

		bigint& operator+=(const bigint& other);
		bigint& operator-=(const bigint& other);
		bigint& operator*=(const bigint& other);
		bigint& operator/=(const bigint& other);
		bigint& operator%=(const bigint& other);

		friend const bigint operator*(const bigint& left, const bigint& right);
		friend const bigint operator/(const bigint& left, const bigint& right);
		friend bool operator==(const bigint&, const bigint&);
		friend bool operator<(const bigint&, const bigint&);
		friend const bigint operator-(const bigint& one);	
		friend std::ostream& operator<<(std::ostream& os, const bigint& self);
		inline unsigned size() const;

	private:
		friend const bigint operator<<(const bigint& one, unsigned size)
		{
			if(size == 0)
				return one;
			bigint result(one);
			result.v.resize(one.size()+size);
			for(int i=one.size()-1; i>=0; --i)
				result.v[size+i] = one.v[i];
			for(unsigned i=0; i<size; ++i)
				result.v[i] = 0;
			return result;
		}
		std::vector<int> v;
		bool postive=true;
	};

	bool operator!=(const bigint&, const bigint&);
	bool operator>(const bigint&, const bigint&);
	bool operator<=(const bigint&, const bigint&);
	bool operator>=(const bigint&, const bigint&);
	inline const bigint operator+(const bigint& left, const bigint& right);
	inline const bigint operator-(const bigint& left, const bigint& right);
	inline const bigint operator%(const bigint& left, const bigint& right);

	inline const bigint operator+(const bigint& left, const bigint& right)
	{
		bigint one=left;
		one+=right;
		return one;
	}

	inline const bigint operator-(const bigint& left, const bigint& right)
	{
		bigint one=left;
		one-=right;
		return one;
	}

	inline unsigned bigint::size() const
	{
		return v.size();
	}

	inline const bigint operator%(const bigint& left, const bigint& right)
	{
		return left - left / right * right;
	}
}
#endif
