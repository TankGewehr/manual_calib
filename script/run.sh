image_path="./data"
image_type="jpg"
pointcloud_path="./data"
pointcloud_type="pcd"
json_path="./data/test.json"
frame_id="test"

./bin/run_lidar2camera $image_path/$frame_id.$image_type $pointcloud_path/$frame_id.$pointcloud_type $json_path
