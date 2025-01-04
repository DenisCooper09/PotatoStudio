#pragma once

#include <vector>
#include <cstdint>

namespace PotatoStudio::Decoders
{
    template<typename TI, typename TO>
    class Decoder
    {
    public:
        void Set(const TI &encoded)
        {
            m_HasDecoded = false;
            m_Encoded    = encoded;
        }

        const TO &Get()
        {
            return m_Decoded;
        }

        virtual void Decode()
        {
            m_HasDecoded = true;
        }

        bool HasDecoded()
        {
            return m_HasDecoded;
        }

    protected:
        TI m_Encoded;
        TO m_Decoded;

    private:
        bool m_HasDecoded = false;
    };
}
