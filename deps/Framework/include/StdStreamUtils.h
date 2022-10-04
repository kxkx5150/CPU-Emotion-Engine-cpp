#pragma once

#include "StdStream.h"

namespace Framework
{
	template <typename StringType>
	CStdStream CreateInputStdStream(const StringType&);

	template <typename StringType>
	CStdStream CreateOutputStdStream(const StringType&);

	template <typename StringType>
	CStdStream CreateUpdateExistingStdStream(const StringType&);

	template <>
	CStdStream CreateInputStdStream(const std::wstring&);

	template <>
	CStdStream CreateInputStdStream(const std::string&);

	template <>
	CStdStream CreateOutputStdStream(const std::wstring&);

	template <>
	CStdStream CreateOutputStdStream(const std::string&);

	template <>
	CStdStream CreateUpdateExistingStdStream(const std::wstring&);

	template <>
	CStdStream CreateUpdateExistingStdStream(const std::string&);
}
