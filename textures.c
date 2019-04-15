#include "wolf3d.h"


int bilinear_filtration(float u, float v, t_texture *texture, int c)
{
	int i1;
	int i2;
	int i3;
	int i4;

	char *ptr;

	ptr = texture->image_data;

	int x = floor(u);
	int y = floor(v);

	i1 = texture->len * y * 4 + x * 4;
	i2 = texture->len * y * 4 + ((x == texture->len - 1) ? 0 : (x + 1)) * 4;
	i3 = texture->len * ((y == texture->len - 1) ? 0 : (y + 1)) * 4 + x * 4;
	i4 = texture->len * ((y == texture->len - 1) ? 0 : (y + 1)) * 4 + ((x == texture->len - 1) ? 0 : (x + 1)) * 4;


	//if (x == texture->len)

	int c1 = ptr[i1 + c];
	//if (c1 > 255)
	//	c1 = 255;
	if (c1 < 0)
		c1 += 255;
	int c2 = ptr[i2 + c];
	//if (c2 > 255)
	//	c2 = 255;
	if (c2 < 0)
		c2 += 255;
	int c3 = ptr[i3 + c];
	//if (c3 > 255)
	//	c3 = 255;
	if (c3 < 0)
		c3 += 255;
	int c4 = ptr[i4 + c];
	//if (c4 > 255)
	//	c4 = 255;
	if (c4 < 0)
		c4 += 255;


	//u *= tex.size;
	//v *= tex.size;
	
	double u_ratio = u - x;
	double v_ratio = v - y;
	double u_opposite = 1 - u_ratio;
	double v_opposite = 1 - v_ratio;
	int result = (int)((c1   * u_opposite  + c2   * u_ratio) * v_opposite + 
                   (c3 * u_opposite  + c4 * u_ratio) * v_ratio);

	//if (result < 0)
	//	result *= -1;
	//if (result > 255)
	//	result = 255;

	return (result);
}



t_rgb get_rgb_from_texture(float col, float row, t_texture *texture, t_wolf3d *wolf3d)
{
	int index;
	t_rgb rgb;
/*
	if (col < 0)
		col *= -1;
	if (row < 0)
		row *= -1;
	if (col > texture->len)
		col = texture->len - 1;
	if (row > texture->len)
		row = texture->len - 1;
*/
	if (wolf3d->filtr)
	{
		rgb.r = bilinear_filtration(col, row, texture, 2);
		rgb.g = bilinear_filtration(col, row, texture, 1);
		rgb.b = bilinear_filtration(col, row, texture, 0);
	}
	else
	{
		int c =(int)col;
		int r = (int)row;
		index = texture->len * r * 4 + c * 4;

		rgb.r = texture->image_data[index + 2];
		rgb.g = texture->image_data[index + 1];
		rgb.b = texture->image_data[index];
	}
	return(rgb);
}
