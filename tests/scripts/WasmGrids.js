/* eslint-env qunit */
QUnit.module('Rasters');


function test_grid_size(grid, V, F, E, A) {
	var grid_attribute_sizes = [
		{ attribute: 'buffer_array_vertex_ids', size: F*3 },
		// { attribute: 'vertex_neighbor_ids', size: V },
		// { attribute: 'vertex_neighbor_count', size: V },
		{ attribute: 'vertex_positions', size: V },
		{ attribute: 'vertex_normals', size: V },
		{ attribute: 'vertex_areas', size: V },
		{ attribute: 'vertex_average_area', size: V },
		{ attribute: 'face_vertex_id_a', size: F },
		{ attribute: 'face_vertex_id_b', size: F },
		{ attribute: 'face_vertex_id_c', size: F },
		// { attribute: 'face_edge_id_a', size: F },
		// { attribute: 'face_edge_id_b', size: F },
		// { attribute: 'face_edge_id_c', size: F },
		{ attribute: 'face_endpoint_a', size: F },
		{ attribute: 'face_endpoint_b', size: F },
		{ attribute: 'face_endpoint_c', size: F },
		{ attribute: 'face_midpoints', size: F },
		{ attribute: 'face_normals', size: F },
		{ attribute: 'face_areas', size: F },
		{ attribute: 'face_average_area', size: F },
		{ attribute: 'edge_vertex_id_a', size: E },
		{ attribute: 'edge_vertex_id_b', size: E },
		// { attribute: 'edge_face_id_a', size: E },
		// { attribute: 'edge_face_id_b', size: E },
		{ attribute: 'edge_endpoint_a', size: E },
		{ attribute: 'edge_endpoint_b', size: E },
		{ attribute: 'edge_midpoints', size: E },
		{ attribute: 'edge_distances', size: E },
		{ attribute: 'edge_average_distance', size: E },
		{ attribute: 'edge_normals', size: E },
		// { attribute: 'edge_areas', size: E },
		{ attribute: 'arrow_vertex_id_from', size: A },
		{ attribute: 'arrow_vertex_id_to', size: A },
		// { attribute: 'arrow_face_id_a', size: A },
		// { attribute: 'arrow_face_id_b', size: A },
		{ attribute: 'arrow_endpoint_from', size: A },
		{ attribute: 'arrow_endpoint_to', size: A },
		{ attribute: 'arrow_midpoints', size: A },
		{ attribute: 'arrow_offsets', size: A },
		{ attribute: 'arrow_distances', size: A },
		{ attribute: 'arrow_average_distance', size: A },
		{ attribute: 'arrow_normals', size: A },
		// { attribute: 'arrow_areas', size: A },
	]
    QUnit.test(`$Grid attributes must have correct size where the Grid has only one face`, function (assert) {
    	for (var grid_attribute_size of grid_attribute_sizes) {
    		var actual_size  = grid[grid_attribute_size.attribute].size();
    		var desired_size = grid[grid_attribute_size.size].size();
	        assert.equal( 
	            actual_size, desired_size,
	            `Grid.${grid_attribute_size.attribute} must have the correct size (${actual_size}==${desired_size})`
	        );
    	}
    });
}

Cpp().then(function(cpp) {

	var grid_with_1_face = new cpp.Grid(
		new cpp.vec3s_from_list([0,0,0,
								 0,0,1,
								 0,1,0]),
		new cpp.uints_from_list([0,1,2])
	);
	test_grid_size(grid_with_1_face, 3, 1, 3, 6);

	var grid_with_2_faces = new cpp.Grid(
		new cpp.vec3s_from_list([0,0,0,
								 0,0,1,
								 0,1,0,
								 0,1,1]),
		new cpp.uints_from_list([0,1,2,
			            	     1,2,3])
	);
	test_grid_size(grid_with_2_faces, 4, 2, 5, 10);

});




