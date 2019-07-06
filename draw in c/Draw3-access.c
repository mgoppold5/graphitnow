/*
 * Copyright (C) 2019  Mike Goppold von Lobsdorf
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * Drawing interface to primitive graphics routines.
 * 
 * This implementation is experimental.  The intention
 * is that all drawing should be done in the heap memory of
 * the server program, using normal language mechanisms.
 */

class Draw3 : public Draw {
public:
	virtual void drawTriangle(
		TypicalInt8Array *resourceStr,
		float32 x1, float32 y1, float32 z1,
		float32 x2, float32 y2, float32 z2,
		float32 x3, float32 y3, float32 z3);
	virtual void drawScene();
	virtual int main();
};