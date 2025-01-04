#pragma once

#include "Decoder.hpp"

namespace PotatoStudio::Decoders
{
    template<typename TI, typename TO, typename T_PARAMS>
    class ParameterizedDecoder : public Decoder<TI, TO>
    {
    public:
        virtual void SetParameters(const T_PARAMS &parameters)
        {
            m_Parameters = parameters;
        }

        virtual const T_PARAMS &GetParameters() const
        {
            return m_Parameters;
        }

    protected:
        T_PARAMS m_Parameters;
    };
}
