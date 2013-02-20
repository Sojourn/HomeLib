#ifndef QUADTREE_H
#define QUADTREE_H

#include <array>
#include <vector>
#include <cstdint>
#include <functional>

namespace Container
{
	struct vec2_t
	{
		float x;
		float y;
	};

	struct aabb_t
	{
		vec2_t center;
		vec2_t extents;
	};

	template<class T>
	class QuadNode
	{
	public:
		const size_t childCount = 4;

		aabb_t bounds;
		std::array<QuadNode<T>*, childCount> children;
	};

	template<class T>
	class QuadTree
	{
	public:
		QuadTree();
		~QuadTree();

	private:
		bool insert(QuadNode *node, const aabb_t &bounds, T &value); 
		bool remove(QuadNode *node, const aabb_t &bounds, T &value);
		void query(QuadNode *node, const aabb_t &bounds, std::function<bool (T &value)> &callback) const;
	};
}

#endif // QUADTREE_H