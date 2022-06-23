/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linkedList.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:34:41 by smia              #+#    #+#             */
/*   Updated: 2022/06/23 23:39:40 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
/*
	First we need to create  a structure
	Type of next pointer
	→ we know that pointer type mean that this pointer should be point on specific type of data int* ⇒ point on int var float......
	so struct node pointer should point to a struct node
 */
typedef struct s_list{
	struct s_list	*prev;
	int				data;
	struct s_list	*next;
}	t_list;

t_list	*new_node(int data)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	tmp->prev = NULL;
	tmp->data = data;
	tmp->next = NULL;
	return (tmp);
}

void	append_in_end(t_list **root, int data)
{
	t_list	*tmp;
	t_list	*p;

	tmp = new_node(data);
	if (!*root)
		*root = tmp;
	else
	{
		p = *root;
		while (p->next)
			p = p->next;
		p->next = tmp;
		tmp->prev = p;
	}
}

/*
	here we check if list is empt 
	if yes we print it if no we print node data and jump to the next node by pointing temp to the next node
*/

void	display_node(t_list *root)
{
	t_list	*temp;

	temp = root;
	if (!root)
		printf("List is empty\n");
	else
	{
		while (temp->next)
			temp = temp->next;
		while(temp)
		{
			printf("%d\n", temp->data);
 			temp = temp->prev;
		}
	}
}

// here we count how many node can p point before point to null 

int	find_len(t_list *root)
{
	int		c;
	t_list	*p;

	c = 0;
	p = root;
	while (p)
	{
		p = p->next;
		c++;
	}
	return (c);
}

/*
	also here we create a node set node→link to null check root if point to a node or not 
	if point to node we point our node to the first node and set root pointer to our node
*/

void	append_start(t_list	**root, int data)
{
	t_list	*tmp;

	tmp = new_node(data);
	if (!*root)
		*root = tmp;
	else
	{
		(*root)->prev = tmp;
		tmp->next = *root;
		*root = tmp;
	}
}

void	append_nth(t_list **top, int data, int nth)
{
	t_list	*node;
	t_list	*tmp;
	int		i;

	node = new_node(data);
	if (!(*top) || nth == 1)
	{
		node->next = (*top);
		(*top)->prev = node;
		*top = node;
		return ;
	}
	tmp = *top;
	i = -1;
	while (++i < nth - 2 && tmp->next)
		tmp = tmp->next;
	node->next = tmp->next;
	tmp->next->prev = node;
	node->prev = tmp;
	tmp->next = node;
}

void	delete_nth(t_list **root, int n)
{
	t_list	*tmp;
	t_list	*tmp1;
	int		i;

	tmp = *root;
	if (!*root || n == 0)
		return ;
	else if (n == 1)
	{
		*root = tmp->next;
		tmp->next->prev = NULL;
		return (free(tmp));
	}
	i = -1;
	while (++i < n - 2 && tmp->next)
		tmp = tmp->next;
	tmp1 = tmp->next;
	tmp->next = tmp1->next;
	tmp1->next->prev = tmp;
	free(tmp1);
}

void	reverse_iterate_linkedlist(t_list **root)
{
	t_list	*cur;
	t_list	*next;
	t_list	*prev;

	cur = *root;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		cur->prev = next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*root = prev;
}

void	display_node_forward_recursion(t_list *root)
{
	if (!root)
		return ;
	else
	{
		printf("%d\n", root->data);
		display_node_forward_recursion(root->next);
	}
}

void	display_node_reversed_recursion(t_list *root)
{
	if (!root)
		return ;
	else
	{
		display_node_reversed_recursion(root->next);
		printf("%d\n", root->data);
	}
}

void	reverse_recursion_linkedlist(t_list **head, t_list *node)
{
	t_list	*tmp;

	if (!node->next)
	{
		node->prev = NULL;
		*head = node;
		return ;
	}
	reverse_recursion_linkedlist(head, node->next);
	tmp = node->next;
	tmp->next = node;
	node->prev = tmp;
	node->next = NULL;
}

void	clr_lst(t_list **root, t_list *node)
{
	if (node == NULL)
		return ;
	clr_lst(root, node->next);
	free(node);
}
