
typedef struct	s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct	s_scope
{
	t_vector 	start;
	t_vector	end;
	float		diff;
}				t_scope;

typedef	struct		s_list
{
	t_scope			*field;
	struct s_list	*next;
	float			diff;
}					t_list;

void	tm_lst_add(t_list **begin, t_list *new)
{
	if (begin && new)
	{
		new->next = *begin;
		*begin = new;
	}
}

void	tm_lst_insert(t_list **first, t_list **second, t_list *new)
{
	*(first)->next = new;
	new->next = *second;
}

t_list	*tm_lst_new(t_scope *field)
{
	t_list		*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->field = field;
	new->diff = abs(field->m_count - field->t_count) / (field->m_count + field->t_count);
	new->next = NULL;
	return (new);
}

void	adding_to_list(t_scope *field)
{
	static t_list	*first;
	t_list			*ptr;
	t_list			*ptr2;

	ptr = first;
	if (first == NULL)
		tm_lst_add(&first, tm_lst_new(&field));
	else
	{
		while (ptr != NULL)
		{
			if (ptr->next != NULL && field->diff <= ptr->diff && field->diff > ptr2->diff)
				tm_lst_insert(&ptr, &ptr->next, tm_lst_new(&field));
			else if (ptr->next == NULL && field->diff <= ptr->diff)
				ptr->next = tm_lst_new(&field);
			else if (field->diff > ptr->diff)
				tm_lst_add(&first, tm_lst_new(&field));
			ptr = ptr->next;
			if (ptr != NULL)
				ptr2 = ptr->next;
		}
	}

}
