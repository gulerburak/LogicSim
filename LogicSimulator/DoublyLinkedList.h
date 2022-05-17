#pragma once

class Node
{
public:
	Node prev*;
	int data;
	Node next*;
	Node()
	{
		prev = NULL;
		next = NULL;
	}
};