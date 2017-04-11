// aria.h - written and placed in the public domain by Jeffrey Walton

//! \file aria.h
//! \brief Classes for the ARIA block cipher
//! \details The Crypto++ ARIA implementation is based on the 32-bit implementation by Aaram Yun
//!   from the National Security Research Institute, KOREA. Aaram Yun's implementation is based on
//!   the 8-bit implementation provided by Jin Hong. The source files are available in ARIA.zip
//!   from the Korea Internet & Security Agency website.
//! \sa <A HREF="http://tools.ietf.org/html/rfc5794">RFC 5794, A Description of the ARIA Encryption Algorithm</A>,
//!   <A HREF="http://seed.kisa.or.kr/iwt/ko/bbs/EgovReferenceList.do?bbsId=BBSMSTR_000000000002">Korea
//!   Internet & Security Agency homepage</A>

#ifndef CRYPTOPP_ARIA_H
#define CRYPTOPP_ARIA_H

#include "config.h"
#include "seckey.h"
#include "secblock.h"

NAMESPACE_BEGIN(CryptoPP)

//! \class ARIA_Info
//! \brief ARIA block cipher information
struct ARIA_Info : public FixedBlockSize<16>, public VariableKeyLength<16, 16, 32, 8>
{
	CRYPTOPP_STATIC_CONSTEXPR const char* StaticAlgorithmName() {return "ARIA";}
};

//! \class ARIA
//! \brief ARIA block cipher
//! \sa <a href="http://www.weidai.com/scan-mirror/cs.html#ARIA">ARIA</a>
class ARIA : public ARIA_Info, public BlockCipherDocumentation
{
public:
	class CRYPTOPP_NO_VTABLE Base : public BlockCipherImpl<ARIA_Info>
	{
	public:
		void UncheckedSetKey(const byte *key, unsigned int keylen, const NameValuePairs &params);
		void ProcessAndXorBlock(const byte *inBlock, const byte *xorBlock, byte *outBlock) const;

	private:
		// Reference implementation allocates a table for 17 sub-keys
		FixedSizeAlignedSecBlock<byte, 16*17> m_rk;  // round keys
		FixedSizeAlignedSecBlock<word32, 4*6> m_w;   // w0, w1, w2, w3 and t
		unsigned int m_rounds;
	};

public:
	typedef BlockCipherFinal<ENCRYPTION, Base> Encryption;
	typedef BlockCipherFinal<DECRYPTION, Base> Decryption;
};

typedef ARIA::Encryption ARIAEncryption;
typedef ARIA::Decryption ARIADecryption;

NAMESPACE_END

#endif