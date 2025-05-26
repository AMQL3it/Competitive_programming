/******************************************************************************
 *----------------------------------------------------------------------------*
 *                                                                            *
 *        If the plan does not work, change the plan but not the goal.        *
 *----------------------------------------------------------------------------*
 *        Life is just a life. Lead it, Feel it & Enjoy It Properly.          *
 *        Nothing is impossible. Just believe in yourself & Almighty.         *
 *----------------------------------------------------------------------------*
 *                                                                            *
 *----------------------------------------------------------------------------*
 ******************************************************************************/

#include<bits/stdc++.h>
using namespace std;

///############################# Typedef Section #############################

typedef unsigned int ui;
typedef long long int ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

///############################################################################

///############################# Define Section ###############################
#define FST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define READ          freopen("in.txt","r",stdin)
#define WRITE         freopen("out.txt","w",stdout);
#define nl            "\n"
// #define pi            acos(-1.0)
#define mem(arr,val)  memset(arr,val,sizeof(arr))
#define pb            push_back
#define mp            make_pair
#define pr            pair<ll,ll>
#define ff            first
#define ss            second
#define mod           1000000007
#define INF           1e18
///############################################################################

///############################# Input Section ################################

#define si1(x)        scanf("%d",&x)
#define si2(x,y)      scanf("%d %d", &x, &y)
#define si3(x,y,z)    scanf("%d %d %d", &x, &y, &z)

#define sd1(x)        scanf("%lf",&x)
#define sd2(x,y)      scanf("%lf %lf", &x, &y)
#define sd3(x,y,z)    scanf("%lf %lf %lf", &x, &y, &z)

#define sli1(x)       scanf("%lld",&x)
#define sli2(x,y)     scanf("%lld %lld", &x, &y)
#define sli3(x,y,z)   scanf("%lld %lld %lld", &x, &y, &z)

///############################################################################
///############################### Index Section ##############################
/*
Building Trees:
    1. From pre-order input
    2. From post-order input
    3. From level-order input
    4. From preoder + inorder input
    5. From postorder + inorder input

Traversal Notes:
    1. Pre-order: Root, Left, Right
    2. Post-order: Left, Right, Root
    3. In-order: Left, Root, Right
    4. Level-order: Root, Left, Right (Level by level)

Build Tree Possibility:

✅ শুধুমাত্র Preorder + null markers (-1) → Tree বানানো সম্ভব  
✅ শুধুমাত্র Postorder + null markers (-1) → Tree বানানো সম্ভব  
✅ শুধুমাত্র Level-order + null markers (-1) → Tree বানানো সম্ভব  
✅ শুধুমাত্র Level-order → Tree বানানো সম্ভব → যদি Complete Binary Tree হয়

✅ [Inorder + Preorder] → Tree বানানো সম্ভব → যদি values **unique** হয়  
✅ [Inorder + Postorder] → Tree বানানো সম্ভব → যদি values **unique** হয়  

❌ শুধুমাত্র Inorder (null সহ বা ছাড়া) → Tree বানানো **অসম্ভব**  
❌ শুধুমাত্র Preorder → Tree বানানো **অসম্ভব** (null না থাকলে)  
❌ শুধুমাত্র Postorder → Tree বানানো **অসম্ভব** (null না থাকলে)  
❌ শুধুমাত্র Level-order → Tree বানানো **অসম্ভব**, যদি tree টি Complete না হয়

*/
///############################################################################
///########################## Binary Tree Structure ###########################

struct node {
    int data;
    struct node *left, *right;

    node(int val) {
        data = val;
        left = right = NULL;
    }
};

using Node = node*;

///###################### Tree Construction Functions #########################

// From Preorder with null markers
Node build_tree_from_preorder_with_null(vector<int> &pre_order, int &idx) {
    if (idx >= pre_order.size() || pre_order[idx] == -1) {
        idx++;
        return NULL;
    }

    Node root = new node(pre_order[idx++]);
    root->left = build_tree_from_preorder_with_null(pre_order, idx);
    root->right = build_tree_from_preorder_with_null(pre_order, idx);
    return root;
}

// From Postorder with null markers
Node build_tree_from_postorder_with_null(vector<int> &post_order, int &idx) {
    if (idx < 0 || post_order[idx] == -1) {
        idx--;
        return NULL;
    }

    Node root = new node(post_order[idx--]);
    root->right = build_tree_from_postorder_with_null(post_order, idx);
    root->left = build_tree_from_postorder_with_null(post_order, idx);
    return root;
}

// From Level-order input with null markers
Node build_tree_from_levelorder_with_null(vector<int> &level_order) {
    if (level_order.empty() || level_order[0] == -1) return NULL;

    queue<Node> q;
    Node root = new node(level_order[0]);
    q.push(root);
    int i = 1;

    while (!q.empty() && i < level_order.size()) {
        Node curr = q.front();
        q.pop();

        if (level_order[i] != -1) {
            curr->left = new node(level_order[i]);
            q.push(curr->left);
        }
        i++;

        if (i < level_order.size() && level_order[i] != -1) {
            curr->right = new node(level_order[i]);
            q.push(curr->right);
        }
        i++;
    }

    return root;
}

// From Preorder + Inorder
Node build_tree_from_pre_in(vector<int>& preorder, vector<int>& inorder, int in_start, int in_end, int& pre_idx, unordered_map<int, int>& inorder_map) {
    if (in_start > in_end) return NULL;

    int root_val = preorder[pre_idx++];
    Node root = new node(root_val);

    int in_index = inorder_map[root_val];
    root->left = build_tree_from_pre_in(preorder, inorder, in_start, in_index - 1, pre_idx, inorder_map);
    root->right = build_tree_from_pre_in(preorder, inorder, in_index + 1, in_end, pre_idx, inorder_map);

    return root;
}

// From Postorder + Inorder
Node build_tree_from_post_in(vector<int>& postorder, vector<int>& inorder, int in_start, int in_end, int& post_idx, unordered_map<int, int>& inorder_map) {
    if (in_start > in_end) return NULL;

    int root_val = postorder[post_idx--];
    Node root = new node(root_val);

    int in_index = inorder_map[root_val];
    root->right = build_tree_from_post_in(postorder, inorder, in_index + 1, in_end, post_idx, inorder_map);
    root->left = build_tree_from_post_in(postorder, inorder, in_start, in_index - 1, post_idx, inorder_map);

    return root;
}

///########################## Tree Traversal Functions ########################

// Preorder Traversal
void print_preorder(Node root) {
    if (!root) return;
    cout << root->data << " ";
    print_preorder(root->left);
    print_preorder(root->right);
}

// Inorder Traversal
void print_inorder(Node root) {
    if (!root) return;
    print_inorder(root->left);
    cout << root->data << " ";
    print_inorder(root->right);
}

// Postorder Traversal
void print_postorder(Node root) {
    if (!root) return;
    print_postorder(root->left);
    print_postorder(root->right);
    cout << root->data << " ";
}

// Level-order / Breadth-first Traversal
void print_levelorder(Node root) {
    if (!root) return;
    queue<Node> q;
    q.push(root);
    // q.push(NULL);
    while (!q.empty()) {
        Node curr = q.front();
        q.pop();
        // if (!curr) {
        //     cout << endl;
        //     if (!q.empty()) q.push(NULL);
        //     continue;
        // }
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

//----------------------------- Basic calculations -----------------------------
/*

- Number of edges: Number of edges in the tree.
- Number of nodes: Number of nodes in the tree.
- Count of nodes: Number of nodes in the tree.
- Sum of nodes: Sum of values of all nodes in the tree.
- Count of leaves: Number of leaf nodes in the tree.
- Depth of a node: Distance (number of edges) from the root to the node.
- Height of a node: Maximum distance from the node to any leaf in its subtree.
- Diameter of a tree: Maximum distance between any two nodes in the tree.

- Size of a subtree: Number of nodes in the subtree.
- Children of a node: Number of children of the node.
- Siblings of a node: Number of siblings of the node.
- Cousins of a node: Number of cousins of the node.



*/

//----------------------------- Count of nodes -----------------------------
ll count_nodes(Node root) {
    if (!root) return 0;
    ll left = count_nodes(root->left);
    ll right = count_nodes(root->right);
    return 1 + left + right;
}

//----------------------------- Sum of nodes -------------------------------
ll sum_of_nodes(Node root) {
    if (!root) return 0;
    ll left = sum_of_nodes(root->left);
    ll right = sum_of_nodes(root->right);
    return root->data + left + right;
}

//----------------------------- Count of leaves -----------------------------
ll count_leaves(Node root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    ll left = count_leaves(root->left);
    ll right = count_leaves(root->right);
    return left + right;
}

//----------------------------- Depth of a node -----------------------------
ll depth(Node root, int target) {
    if (!root) return 0;
    if (root->data == target) return 0;
    ll left = depth(root->left, target);
    ll right = depth(root->right, target);
    return 1 + max(left, right);
}

//----------------------------- Height of a node -----------------------------
ll height(Node root) {
    if (!root) return 0;
    ll left = height(root->left);
    ll right = height(root->right);
    return 1 + max(left, right);
}


//----------------------------- Diameter of Tree -----------------------------
int diameter(Node root) {   // Time Complexity: O(N^2)
    if (!root) return 0;
    int left_height = height(root->left);
    int right_height = height(root->right);
    int left_diameter = diameter(root->left);
    int right_diameter = diameter(root->right);
    return max(1 + left_height + right_height, max(left_diameter, right_diameter));
}

struct TreeInfo {
    int height;
    int diameter;
    TreeInfo(int h, int d) {
        height = h;
        diameter = d;
    }
};

TreeInfo diameter_fast(Node root) {   // Time Complexity: O(N)
    if (!root) return TreeInfo(0, 0);
    TreeInfo left = diameter_fast(root->left);
    TreeInfo right = diameter_fast(root->right);
    int my_height = 1 + max(left.height, right.height);
    int my_diameter = max(1 + left.height + right.height, max(left.diameter, right.diameter));
    return TreeInfo(my_height, my_diameter);
}

// Lowest Common Ancestor (LCA)
Node lca(Node root, int n1, int n2) {
    if (!root) return NULL;
    if (root->data == n1 || root->data == n2) return root;
    Node left = lca(root->left, n1, n2);
    Node right = lca(root->right, n1, n2);
    if (left && right) return root;
    return left ? left : right;
}

// Path from Root to Node
vector<int> path_from_root(Node root, int target) {
    vector<int> path;
    while (root && root->data != target) {
        path.push_back(root->data);
        if (root->data > target) root = root->left;
        else root = root->right;
    }
    path.push_back(root->data);
    return path;
}


///############################# Main Function ###############################

void DenTofieM() {
    // Example Inputs:
    vector<int> pre_order_with_null = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
    vector<int> post_order_with_null = {-1,-1,4,-1,-1,5,2,-1,-1,-1,6,3,1};
    vector<int> level_order_with_null = {1, 2, 3, 4, 5, -1, 6, -1, -1, -1, -1, -1, -1};
    vector<int> preorder = {1, 2, 4, 5, 3, 6};
    vector<int> inorder = {4, 2, 5, 1, 3, 6};
    vector<int> postorder = {4, 5, 2, 6, 3, 1};

    unordered_map<int, int> inorder_map;
    for (int i = 0; i < inorder.size(); i++) {
        inorder_map[inorder[i]] = i;
    }

    // Choose any construction:
    // 1. From Preorder + null
    // int idx = 0;
    // Node root = build_tree_from_preorder_with_null(pre_order_with_null, idx);

    // 2. From Postorder + null
    // int idx = post_order_with_null.size() - 1;
    // Node root = build_tree_from_postorder_with_null(post_order_with_null, idx);

    // 3. From Level-order + null
    // Node root = build_tree_from_levelorder_with_null(level_order_with_null);

    // 4. From Preorder + Inorder
    // int pre_idx = 0;
    // Node root = build_tree_from_pre_in(preorder, inorder, 0, inorder.size() - 1, pre_idx, inorder_map);

    // 5. From Postorder + Inorder
    int post_idx = postorder.size() - 1;
    Node root = build_tree_from_post_in(postorder, inorder, 0, inorder.size() - 1, post_idx, inorder_map);

    cout << "Depth: " << depth(root) << nl;
    cout << "Height: " << height(root) << nl;
    cout << "Nodes: " << count_nodes(root) << nl;
    cout << "Leaves: " << count_leaves(root) << nl;
    cout << "Diameter: " << diameter(root) << nl;
    cout << "LCA: " << lca(root, 4, 3)->data << nl;
    // cout << "Path from Root to Node: ";
    // for (int i : path_from_root(root, 4)) cout << i << " ";
    // cout << nl;

    // Output Traversals
    // cout << "Preorder: "; print_preorder(root); cout << nl;
    // cout << "Inorder: "; print_inorder(root); cout << nl;
    // cout << "Postorder: "; print_postorder(root); cout << nl;
    // cout << "Levelorder: \n"; print_levelorder(root); cout << nl;
}

int main() {
    FST_IO
    DenTofieM();
    return 0;
}