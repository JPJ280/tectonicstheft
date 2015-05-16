JsonSerializer = {};
JsonSerializer.serialize = function(world) {
	var supercontinentCycle = world.supercontinentCycle;

	var world_json = {
		radius: world.radius,
		platesNum: world.platesNum,
		mountainWidth: world.mountainWidth,
		age: world.age,
		plates: [],
		grid: undefined,
		supercontinentCycle: {
			duration: supercontinentCycle.duration,
			age: supercontinentCycle.age,
			oldSupercontinentPos: supercontinentCycle.oldSupercontinentPos,
			newSupercontinentPos: supercontinentCycle.newSupercontinentPos,
		},
	};

	for (var i = 0, li = world.plates.length; i < li; i++) {
		plate = world.plates[i]
		var plate_json = {
			eulerPole: 		plate.eulerPole,
			angularSpeed: 	plate.angularSpeed,
			densityOffset: 	plate.densityOffset,
			rockColumns: 	[],
		};
		for (var j = 0, lj = plate._cells.length; j < lj; j++) {
			var cell = plate._cells[j];
			if(!cell.content){
				continue;
			}
			var rockColumn = cell.content;
			var rockColumn_json = 
			[
				j,
				Math.round(rockColumn.thickness),
				Math.round(rockColumn.density),
			]
			plate_json.rockColumns.push(rockColumn_json);
			// plate_json.rockColumns.push.apply(plate_json.rockColumns, rockColumn_json);
		};
		world_json.plates.push(plate_json);
	};
	return {
		version: 0,
		seed: seed,
		world: world_json
	};
};
JsonSerializer.deserialize = function(json) {
	seed = json.seed;
	random = new Random(parseSeed(seed));

	var world = new World(grid,	{
		radius: json.world.radius,
		platesNum: json.world.platesNum,
		mountainWidth: json.world.mountainWidth,
		age: json.world.age,

		supercontinentCycle: undefined,
		plates: [],
	});
	world.plates = json.world.plates.map(function(plate_json){
		var plate = new Plates(world, {
			eulerPole: plate_json.eulerPole,
			angularSpeed: plate_json.angularSpeed,
			densityOffset: plate_json.densityOffset
		});
		for (var i = 0, li = plate_json.rockColumns.length; i < li; i--) {
			var rockColumn_json = plate_json.rockColumns[i];
			if(!rockColumn){
				continue;
			}
			var rockColumn = new RockColumn(world, {
				thickness: rockColumn_json[1],
				density: rockColumn_json[2]
			});
			rockColumn.isostasy();
			plates._cells[rockColumn_json[0]] = rockColumn;
		};
	});
	world.updateNeighbors();
	world.updateBorders();
	world.supercontinentCycle = new SupercontinentCycle(world, {

	});
	return world;
}