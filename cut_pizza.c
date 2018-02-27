#include "pizza.h"

void 	cut_scope(t_scope *scope)
{
	int	x_start = scope->start.x;
	int	y_start = scope->start.y;


}

void	start_cut(void)
{
	t_list	*sc = scopes;

	while (sc)
	{
		cut_scope(sc->scope);
		sc = sc->next;
	}
}
