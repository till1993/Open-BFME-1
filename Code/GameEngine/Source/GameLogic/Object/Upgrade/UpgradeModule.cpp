// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <bitset>

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

template<>
class BitFlags<192>
{
public:
	bool any() const { return m_bits.any(); }
	bool testForAny(const BitFlags &) const;
	bool testForAll(const BitFlags &) const;
	bool testForNone(const BitFlags &) const;

private:
	_STL::bitset<192> m_bits;
};

class UpgradeMux
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void getUpgradeActivationMasks(BitFlags<192> &, BitFlags<192> &) const;
	virtual void slot2C();
	virtual bool requiresAllActivationUpgrades() const;

	virtual bool testUpgradeConditions(const BitFlags<192> &keyMask) const;
};

bool UpgradeMux::testUpgradeConditions(const BitFlags<192> &keyMask) const
{
	BitFlags<192> activation;
	BitFlags<192> conflicting;
	getUpgradeActivationMasks(activation, conflicting);

	if (activation.any())
	{
		const BitFlags<192> *mask = &keyMask;
		if (conflicting.testForNone(*mask))
		{
			if (requiresAllActivationUpgrades())
				return mask->testForAll(activation);
			return mask->testForAny(activation);
		}
	}
	return false;
}
