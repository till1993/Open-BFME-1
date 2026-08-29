// cl: /DNDEBUG /MD /EHsc

template<int BitCount>
class BfmeBitSet
{
public:
	BfmeBitSet()
	{
		for (unsigned int i = 0; i < 6; ++i)
			m_bits[i] = 0;
	}

	BfmeBitSet &operator&=(const BfmeBitSet &that)
	{
		for (unsigned int i = 0; i < 6; ++i)
			m_bits[i] &= that.m_bits[i];
		return *this;
	}

	bool any() const
	{
		for (unsigned int i = 0; i < 6; ++i)
			if (m_bits[i])
				return true;
		return false;
	}

	unsigned int m_bits[6];
};

template<int BitCount>
class BitFlags
{
public:
	bool testForNone(const BitFlags &that) const
	{
		BitFlags intersection = *this;
		intersection.m_bits &= that.m_bits;
		return !intersection.m_bits.any();
	}

private:
	BfmeBitSet<BitCount> m_bits;
};

template bool BitFlags<187>::testForNone(const BitFlags<187> &) const;
