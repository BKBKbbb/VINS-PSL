#ifndef READ_CONFIGS_H_
#define READ_CONFIGS_H_

#include <ros/ros.h>
#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>

struct PLNetCOnfig
{
	PLNetCOnfig() {}
	//load config file
	void load(const std::string &config_file)
	{
		FILE *fh = fopen(config_file.c_str(), "r");
		if(fh == NULL)
		{
			ROS_WARN("config file does not exist; wrong file path");
			ROS_BREAK();
			return;
		}
		cv::FileStorage fsSettings(config_file, cv::FileStorage::READ);
		fsSettings["plnet.superpoint_onnx_model"] >> superpoint_onnx;
		fsSettings["plnet.superpoint_trt_model"] >> superpoint_engine;

		fsSettings["plnet.plnet_s0_onnx_model"] >> plnet_s0_onnx;
		fsSettings["plnet.plnet_s0_trt_model"] >> plnet_s0_engine;
		fsSettings["plnet.plnet_s1_onnx_model"] >> plnet_s1_onnx;
		fsSettings["plnet.plnet_s1_trt_model"] >> plnet_s1_engine;

		use_superpoint = fsSettings["plnet.use_superpoint"];

		max_keypoints = fsSettings["plnet.max_keypoints"];
		keypoint_threshold = fsSettings["plnet.keypoint_threshold"];
		remove_borders = fsSettings["plnet.remove_borders"];

		line_threshold = fsSettings["plnet.line_threshold"];
		line_length_threshold = fsSettings["plnet.line_length_threshold"];
	}
	void setModelPrefixPath(std::string model_prefix_path)
	{
		if(model_prefix_path.back() != '/')
			model_prefix_path += '/';
		superpoint_onnx = model_prefix_path + superpoint_onnx;
		superpoint_engine = model_prefix_path + superpoint_engine;
		plnet_s0_onnx = model_prefix_path + plnet_s0_onnx;
		plnet_s0_engine = model_prefix_path + plnet_s0_engine;
		plnet_s1_onnx = model_prefix_path + plnet_s1_onnx;
		plnet_s1_engine = model_prefix_path + plnet_s1_engine;
	}

	std::string superpoint_onnx;
	std::string superpoint_engine;

	std::string plnet_s0_onnx;
	std::string plnet_s0_engine;
	std::string plnet_s1_onnx;
	std::string plnet_s1_engine;

	int use_superpoint;

	int max_keypoints;
	float keypoint_threshold;
	int remove_borders;

	float line_threshold;
	float line_length_threshold;
};

struct SuperPointConfig
{
	int max_keypoints;
	float keypoint_threshold;
	int remove_borders;
	int dla_core;
	std::vector<std::string> input_tensor_names;
	std::vector<std::string> output_tensor_names;
	std::string onnx_file;
	std::string engine_file;
};

struct PointMatcherConfig 
{
	int matcher;
	int image_width;
	int image_height;
	int dla_core;
	std::vector<std::string> input_tensor_names;
	std::vector<std::string> output_tensor_names;
	std::string onnx_file;
	std::string engine_file;
	PointMatcherConfig() {}

	void load(const std::string &config_file)
	{
		FILE *fh = fopen(config_file.c_str(), "r");
		if(fh == NULL)
		{
			ROS_WARN("config file does not exist; wrong file path");
			ROS_BREAK();
			return;
		}
		cv::FileStorage fsSettings(config_file, cv::FileStorage::READ);

		matcher = fsSettings["matcher"];
		image_width = fsSettings["image_width"];
		image_height = fsSettings["image_height"];
		fsSettings["onnx_file"] >> onnx_file;
		fsSettings["engine_file"] >> engine_file;
	}

	void setModelPrefixPath(std::string model_prefix_path)
	{
		if(model_prefix_path.back() != '/')
			model_prefix_path += '/';
		onnx_file = model_prefix_path + onnx_file;
		engine_file = model_prefix_path + engine_file;
	}

};

#endif