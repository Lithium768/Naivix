/*
	  Copyright 2017, Lithium768 <tianxiangli768@gmail.com>

	  This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	  This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	  You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __VAARG_H__
#define __VAARG_H__

#ifndef __ASM__

#define			VA_START(ap, last_parm)			__builtin_va_start(ap, last_parm)
#define			VA_END(ap)						__builtin_va_end(ap)
#define			VA_ARG(ap, type)				__builtin_va_arg(ap, type)

typedef __builtin_va_list VA_LIST;

#endif /* __ASM__ */

#endif /* __VAARG_H__ */
