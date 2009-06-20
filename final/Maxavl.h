#ifndef MAXAVL_H
#define MAXAVL_H

/*
 *
 *	Maxavl.h
 *
 */
#include <cstddef>

template <typename T>
class MAXAVL{
public:

	enum AVLReturnCodes
	{	
		Success,
		Item_already_exist,
		Item_doesnt_exist
	};

	// A unary predicate class - used to preform operations on the items in the tree
	// while traversal the tree
    // return true to stop the tree-traversal 
	class Predicate{
	public:
		virtual bool DoWork(T* item) = 0;
	};

	MAXAVL() : root(NULL) {};

	void DestroyTree(bool FreeItems)
	{
		Destroy(root,FreeItems);
		root = NULL;
	}



	//results of the compare function
	//number so it will be easy to convert compare result and direction
	//to continue search
	enum CmpResult
	{
		Bellow=0,
		Above=1,
		Equal
	};

	// returns the Height of the tree
	int Height() const
	{
		int Height = -1;
		node* ptr = root;
		while (ptr != NULL)
		{
			ptr = ptr->bf > 0 ? ptr->Children[Left] :  ptr->Children[Right];
			Height++;
		}
		return Height;
	}


	//traverse the tree in order until p->dowork return true
	//calls p->DoWork on each item in the tree
	// notice: if you want to change an item in a way that effects how
	// it compares to other items, you should remove it from the tree
	// make the change and reinsert it.
	void inorder(Predicate *p) const
	{
		inorder(root,p);
	}

	// inserts the item to the tree. The item is added AS-IS - 
    // no copy of the pointed item is created
	// notice: if you want to change an item in a way that effects how
	// it compares to other items, you should remove it from the tree
	// make the change and reinsert it.
	// Warning: might throw std::bad_alloc
	AVLReturnCodes insert(T *item)
	{
		return insert(root, item) != Error ?  Success : Item_already_exist;
	}

	// removes an item from the tree, the argument
	// should be an item which is equal to the item
	// to remove according to the <= function
	T* remove(T *item)
	{
		return remove(root, item) != Error ?  item : NULL;
	}

	// retrieves an item from the tree, the argument
	// should be an item which is equal to the item
	// to find according to the <= function
	T* find(T *item) const
	{
		node* ptr = root;
		while  (ptr != NULL)
		{
			CmpResult res= Cmp(ptr->data,item);
			if (res == Equal)
			{
				return ptr->data; //item found
			}
			//else
			directions dir = (directions) res; //bellow -> left, above -> right
			ptr = ptr->Children[dir];
		}
		return NULL; //if we arrive here item wasn't found
	}

	//return the minimal item in the tree according to <=,
	//or null if the tree is empty
	T* GetMax() const
	{
		node* ptr = root;
		T* item;
		while (ptr != NULL)
		{
			item = ptr->data;
			ptr = ptr->Children[Right];
		}
		return item;
	}

	// retrieves the Closest item in Dir directions from the tree
	// according to the <= function
	T* findClosest(T *item, CmpResult res, int& Min, int& Max) const
	{
		Min = Max = -1;
		return Closest(root,item,(directions)res, Min, Max);
	}


private:
	MAXAVL(const MAXAVL&) {}; //no copying of tree is allowed
	static const int NumberOfChildren = 2;

	 // internal class - not needed for usage of Tree
	class node
	{
	public:
		node(T *newdata) : data(newdata),Max(-1),Min(-1),bf(0)
		{
			Min = Max = newdata->AValue();
			Children[Left]=Children[Right] = NULL;
		}
		T *data;
		int Max; //maximum of subtree
		int Min;

		node* Children[NumberOfChildren];
		int bf;
	};

	//direction, or the indexes of the children of a node
	enum directions
	{
		Left=0,
		Right=1
	};

	//return values of various recursive function
	//tells the caller if the height changed or not
	//and if there was an error
	enum HeightChange
	{
		NoHeightChange,
		HeightChanged,
		Error //problem in insert, remove, etc..
	};

	//receives a direction and returns the opposite direction
	static inline directions OtherDirection(directions dir)
	{
		return  (directions) (1 - dir);
	}


	static int Max(int x, int y)
	{
		return x > y ? x : y;
	}

	static int Min(int x, int y)
	{
		//we want -1 to be consider as larger then any value
		return (unsigned int)x < (unsigned int)y ? x : y;
	}

	static inline int GetMax(node* Node)
	{
		return Node == NULL ? -1 : Node->Max;
	}

	static inline int GetMin(node* Node)
	{
		return Node == NULL ? -1 : Node->Min;
	}

	static void UpdateMinMax(node* root)
	{
		root->Min = root->Max = root->data->AValue();
		for (int dir = Left; dir <= Right; dir++)
		{
		
			root->Max = Max(GetMax(root->Children[directions (dir)]),root->Max);
			
			root->Min = Min(GetMin(root->Children[directions (dir)]),root->Min);
			
		}
	}
	
	//calc the bfchange if a balanced tree grow by 1 in dir direction
	//if dir = left we need to add 1 to bf, if 
	//dir == right we need to add -1 to bf
	static inline int CalcBfChange(directions Dir)
	{
		return (1 - 2 * Dir);
	}

	//compares two items using <= and returns result
	static CmpResult Cmp(const T* x,const T* y)
	{
		if (*y <= *x)
		{
			if (*x <= *y)
			{
				//*x == *y
				return Equal;
			}
			//*x < *y
			return Bellow;
		}
		else
		{
			//*x > *y
			return Above;
		}
	}


	//receives the root and the change in bf, updates Bf and
	//preforms roll if necessary and returns whether a roll occurred
	static bool UpdateBalance(node* &root,int BfChange)
	{
		root->bf += BfChange;
		if (root->bf == 2*BfChange)
		{
			directions RollDirection = root->bf == 2 ? Right : Left; //if we arrive here bf is either 2 or -2
			//if its two need to roll to the right otherwise to the left
			directions OppositeDirection = OtherDirection(RollDirection); 
				
			if (root->Children[OppositeDirection]->bf == CalcBfChange(RollDirection))
			{	//if direction is Right(=0), we need
				//to check if the left subtree's bf is -1 and if is is do LR roll
				//if direction is Left(=1), we need
				//to check if the Right subtree's bf is 1 and if it is do RL roll

				//LR or RL roll
				Roll(root->Children[OppositeDirection],OppositeDirection,RollDirection);
				Roll(root,RollDirection,OppositeDirection);
			}
			else
			{
				//LL or RR roll
				Roll(root,RollDirection,OppositeDirection);
			}
			return true;
		}
		return false;
	}

	//preforms a roll in RollDirection to the subtree whose root is root
	static void Roll(node* &root, directions RollDirection, directions OppositeDirection)
	{
		node* ptr = root->Children[OppositeDirection];
		root->Children[OppositeDirection] = ptr->Children[RollDirection];
		ptr->Children[RollDirection] = root;
		

		int BfValue = CalcBfChange(RollDirection); //1 for left -1 for right

		//balance updates
		//description for left roll (other side is symmetric)
		//old root:
		//we lose the right child, and the child's right child
		//so first we decrease one for child
		//second we check if the right child's right subtree is bigger
		//the right child's left sub tree if it is we also gain the difference between the subtrees
		root->bf +=  BfValue;
		if (ptr->bf * BfValue < 0)
		{
			root->bf -=  ptr->bf;
		}

		//description for left roll (other side is symmetric)
		//new root:
		//in the new root we gain the old root as the left child,
		//now we have to check if our old left subtree is smaller then
		//the oldroot left subtree, if it his we also gain this difference
		//we can preform this check according to the old root new bfvalue
		ptr->bf  +=  BfValue;
		if (root->bf * BfValue > 0)
		{
			ptr->bf +=  root->bf;
		}

		
		UpdateMinMax(root);
		UpdateMinMax(ptr);
		

		root = ptr; //update root
	}

	//internal insert function
	static HeightChange insert(node* &root,T *item)
	{
		if (root == NULL)
		{
			root = new node(item);
			return HeightChanged;
		}	
		//else
		CmpResult res= Cmp(root->data,item);
		if (res == Equal)
		{
			//we arrive here if the item already exist
			return Error;
		}
		else
		{
			directions dir = (directions) res; //bellow -> left, above -> right
			HeightChange height = insert(root->Children[dir],item);
			
			UpdateMinMax(root);
			
			if (height == HeightChanged)
			{
				if (UpdateBalance(root,CalcBfChange(dir)) || root->bf == 0)
				{
					//if the tree is balanced now it was imbalanced we didn't change the height,
					//if its -1 or 1 it means that one of the sides grow
					height = NoHeightChange;
				}
			}
			return height;
		}
	}

	//internal remove function
	static HeightChange remove(node* &root,T* &item)
	{
		if (root == NULL)
		{
			return Error; //item wasn't found
		}

		//else
		int BfChange;
		HeightChange height;
		CmpResult res= Cmp(root->data,item);
		if (res == Equal)
		{
			item = root->data; //return item to caller
		
			//found item need to delete it
			if (root->Children[Right] == NULL) //we don't have right child
			{
				node* ptr = root; //save pointer to root to free it
			    root = root->Children[Left]; //make the left child (or null) the name child of parent
				delete ptr; //free node;
				return HeightChanged; //we changed the height
			}
			else //we have a right child
			{
				//extract the minimum of the sub tree and put it in root
				height = ExtractMin(root->Children[Right],root->data);
				BfChange = 1;
			}
		}
		else
		{
			directions dir = (directions) res; //bellow -> left, above -> right
			BfChange = -CalcBfChange(dir);
			height = remove(root->Children[dir],item); 
		}
		
		
		UpdateMinMax(root);
		
		if (height == HeightChanged)
		{
			if ((UpdateBalance(root,BfChange) && root->bf != 0)
				|| root->bf != 0)
			{
				height = NoHeightChange; //if we preformed a roll and the tree still isn't balanced
				//or if we didn't, the tree was balanced but now it isn't then the height didn't change
			}
		}
		return height;	
	}

	//Extract the minimum from the tree and put it in Min
	//could be done with getmin + remove, but then we would travel
	//the tree twice and do unnecessary compares
	static HeightChange ExtractMin(node* &root,T* &Min)
	{
		if (root->Children[Left] == NULL)
		{
			node* ptr = root->Children[Right];
			Min = root->data;
			delete(root); //free node
			root = ptr; //update the child of the parent to point to the right child
			return HeightChanged; //we deleted a node so the height changed
		}
		//else
		HeightChange height = ExtractMin(root->Children[Left],Min);
		
		UpdateMinMax(root);
		
		if (height == HeightChanged)
		{
			if ((UpdateBalance(root,-1) && root->bf != 0)
					|| root->bf != 0)
			{
				height = NoHeightChange; //if we preformed a roll and now the tree is balanced,
				//or if we didn't, the tree was balanced but now it isn't then the height didn't change
			}
		}
		return height;
	}

	//finds closest item in dir and the maximum in opposite direction
	static T* Closest(node* root,T *item, directions Dir, int& rMin, int& rMax)
	{
		int myMax = rMax; 
		int myMin = rMin;
		while  (root != NULL)
		{
			CmpResult res= Cmp(root->data,item);
			if (res != (CmpResult)Dir)
			{
				
				rMax = myMax = Max(Max(myMax,root->data->AValue()),GetMax(root->Children[Dir]));
				rMin = myMin = Min(Min(myMin,root->data->AValue()),GetMin(root->Children[Dir]));
				
				T* InSubTree = Closest(root->Children[OtherDirection(Dir)],item,Dir,rMin,rMax);
				if (InSubTree == NULL || Cmp(InSubTree,root->data)!=(CmpResult)Dir) 
				{
					rMax = myMax;
					rMin = myMin;
					return root->data;
				}
				else
				{
					//rin, rmax is alreay up to date
					return InSubTree;
				}
			}
			//else
			
			
			root = root->Children[Dir];
		}
		rMin = rMax = -1;
		return NULL; //if we arrive here item wasn't found
	}

	//internal inorder function
	static bool inorder(node* root,Predicate *p)
	{
		if (root != NULL)
		{
			return inorder(root->Children[Left],p)
				|| p->DoWork(root->data)
				|| inorder(root->Children[Right],p);
		}
		return false;
	}

	//internal free function
	static void Destroy(node* root,bool FreeItems)
	{
		if (root != NULL)
		{
			Destroy(root->Children[Left],FreeItems);
			Destroy(root->Children[Right],FreeItems);
			if (FreeItems)
			{
				delete root->data;
			}
			delete root;
		}
	}


	node* root;
};

#endif

