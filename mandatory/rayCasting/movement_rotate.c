/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalek <asalek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:23:44 by asalek            #+#    #+#             */
/*   Updated: 2022/07/17 16:42:30 by asalek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_player(t_all *t)
{
	if (t->mlx->analog.right_arrow == 1)
	{
		double oldDirX = t->ray->dirx;
		double oldPlaneX = t->ray->planex;
		
		t->ray->dirx = t->ray->dirx * cos(-ROTATE_SPEED)\
			- t->ray->diry * sin(-ROTATE_SPEED);
		t->ray->diry = oldDirX * sin(-ROTATE_SPEED)\
			+ t->ray->diry * cos(-ROTATE_SPEED);
		t->ray->planex = t->ray->planex * cos(-ROTATE_SPEED)\
			- t->ray->planey * sin(-ROTATE_SPEED);
		t->ray->planey = oldPlaneX * sin(-ROTATE_SPEED)\
			+ t->ray->planey * cos(-ROTATE_SPEED);
	}
	if (t->mlx->analog.left_arrow == 1)
	{
		double oldDirX = t->ray->dirx;
		double oldPlaneX = t->ray->planex;
		
		t->ray->dirx = t->ray->dirx * cos(ROTATE_SPEED)\
			- t->ray->diry * sin(ROTATE_SPEED);
		t->ray->diry = oldDirX * sin(ROTATE_SPEED)\
			+ t->ray->diry * cos(ROTATE_SPEED);
		t->ray->planex = t->ray->planex * cos(ROTATE_SPEED)\
			- t->ray->planey * sin(ROTATE_SPEED);
		t->ray->planey = oldPlaneX * sin(ROTATE_SPEED)\
			+ t->ray->planey * cos(ROTATE_SPEED);
	}
}

void	s_key(t_all *t)
{
	if (t->mlx->analog.s == 1)
	{
		if (t->map[(int)(t->ray->posx - SPEED * t->ray->dirx)] \
		[(int)t->ray->posy] != '1')
			t->ray->posx = t->ray->posx - SPEED * t->ray->dirx;
		if (t->map[(int)t->ray->posx] \
		[(int)(t->ray->posy - t->ray->diry * SPEED)] != '1')
			t->ray->posy = t->ray->posy - SPEED * t->ray->diry;
	}
	if (t->mlx->analog.w == 1)
	{
		if (t->map[(int)(t->ray->posx + SPEED * t->ray->dirx)] \
		[(int)t->ray->posy] != '1')
			t->ray->posx = t->ray->posx + SPEED * t->ray->dirx;
		if (t->map[(int)t->ray->posx] \
		[(int)(t->ray->posy + t->ray->diry * SPEED)] != '1')
			t->ray->posy = t->ray->posy + SPEED * t->ray->diry;
	}
}

void	doors_open_close(t_all *t)
{
	int	i;
	int	j;

	i = -1;
	while (t->map[++i])
	{
		j = -1;
		while (t->map[i][++j])
		{
			if (t->map[i][j] == '2' && (fabs(i - t->ray->posx)))
				t->map[i][j] = '3';				
			if (t->map[i][j] == '3' && (fabs(j - t->ray->posy) >= 3))
				t->map[i][j] = '2';				
		}
	}
}

int	player_movement(t_all *t)
{
	if (t->mlx->analog.a == 1)
	{
		if (t->map[(int)t->ray->posx] \
		[(int)(t->ray->posy - SPEED * t->ray->planey)] != '1')
			t->ray->posy = t->ray->posy - SPEED * t->ray->planey;
		if (t->map[(int)(t->ray->posx - SPEED * t->ray->planex)] \
		[(int)(t->ray->posy)] != '1')
			t->ray->posx = t->ray->posx - SPEED * t->ray->planex;
	}
	if (t->mlx->analog.d == 1)
	{
		if (t->map[(int)t->ray->posx] \
		[(int)(t->ray->posy + SPEED * t->ray->planey)] != '1')
			t->ray->posy = t->ray->posy + SPEED * t->ray->planey;
		if (t->map[(int)(t->ray->posx + t->ray->planex * SPEED)] \
		[(int)(t->ray->posy)] != '1')
			t->ray->posx = t->ray->posx + t->ray->planex * SPEED;
	}
	s_key(t);
	rotate_player(t);
	doors_open_close(t);
	paint_on_screen(t->ray, t->mlx, t->map);
	return (0);
}
