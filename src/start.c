/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:58:31 by damachad          #+#    #+#             */
/*   Updated: 2023/07/26 14:00:08 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// Handle keypresses, and exit if 'ESC' is pressed (events)

int	quit_prog(t_game *game)
{
	destroy_game(game);
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int keysym, t_game *game)
{
    if (keysym == XK_Escape)
		quit_prog(game);
	else if (keysym == XK_w)
		game->next = (t_point){game->curr.x, game->curr.y - 1};
	else if (keysym == XK_a)
		game->next = (t_point){game->curr.x - 1, game->curr.y};
	else if (keysym == XK_s)
		game->next = (t_point){game->curr.x, game->curr.y + 1};
	else if (keysym == XK_d)
		game->next = (t_point){game->curr.x + 1, game->curr.y};
	return (keysym);
}

// Initialize graphics using mlx_init() and mlx_new_window()

void	init_graphics(t_game *game)
{
	game->display.mlx = mlx_init();
	if (!game->display.mlx)
		error_msg(game, "mlx_init() failed\n");
	game->display.win = mlx_new_window(game->display.mlx, game->map->columns * 32, \
	game->map->rows * 32, "so_long"); //why 32? (32 is the size of the sprites)
	if (!game->display.win)
		error_msg(game, "mlx_new_window() failed\n");
}

// Initialize 't_game' struct, load and check map,
// initialize graphics, load sprites, render map,
// and start game loop

void	start_game(char	*mapfile)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	load_map(&game, mapfile);
	validate_map(&game);
//	print_img(&game);
	init_graphics(&game);
	load_sprites(&game);
	render_map(&game);
	mlx_hook(game.display.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.display.win, DestroyNotify, KeyPressMask, quit_prog, &game);
	mlx_loop_hook(game.display.mlx, render_frame, &game);
	mlx_loop(game.display.mlx);
//	quit_prog(&game);
}

// Load sprites from xpm files (defined in macros) using mlx_xpm_file_to_image()

void	load_sprites(t_game *game)
{
	game->sprites = malloc(5 * sizeof(t_sprite));
	if (!game->sprites)
		error_msg(game, "Could not allocate memory for sprites.\n");
	game->sprites[0].img = mlx_xpm_file_to_image(game->display.mlx, \
	FLOOR, &(game->sprites[0].width), &(game->sprites[0].height));
	game->sprites[1].img = mlx_xpm_file_to_image(game->display.mlx, \
	WALL, &(game->sprites[1].width), &(game->sprites[1].height));
	game->sprites[2].img = mlx_xpm_file_to_image(game->display.mlx, \
	COLLECT, &(game->sprites[2].width), &(game->sprites[2].height));
	game->sprites[3].img = mlx_xpm_file_to_image(game->display.mlx, \
	EXIT, &(game->sprites[3].width), &(game->sprites[3].height));
	game->sprites[4].img = mlx_xpm_file_to_image(game->display.mlx, \
	PLAYER, &(game->sprites[4].width), &(game->sprites[4].height));
}
/*
void	print_img(t_game *game)
{
	printf("Width: %d\n", game->display.width);
	printf("Height: %d\n", game->display.height);
	printf("BPP: %d\n", game->display.bpp);
	printf("Endian: %d\n", game->display.endian);
	printf("Line lenght: %d\n", game->display.line_len);
	mlx_loop
}
*/