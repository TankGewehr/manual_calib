#pragma once

#include <iostream>
#include"jsoncpp/json/json.h"

void LoadIntrinsic(const std::string &filename,Eigen::Matrix3d &K,std::vector<double> &dist)
{
	Json::Reader reader;
	Json::Value root;
	std::vector<double> intrinsic;
	std::vector<double> distortion;

	std::ifstream is(filename,std::ios::binary);
	if(!is.is_open())
	{
		std::cout<<"Error opening file:"<<filename<<std::endl;
		return;
	}

	if(reader.parse(is,root))
	{
		//read intrinsic[9] or intrinsic[3][3]
		if(!root["undistort_intrinsic"].isNull()&&root["undistort_intrinsic"].type()==Json::arrayValue)
		{
			if(root["undistort_intrinsic"].size()==3)
			{
				for(unsigned int i=0;i<root["undistort_intrinsic"].size();i++)
				{
					if(root["undistort_intrinsic"][i].isNull()||root["undistort_intrinsic"][i].type()!=Json::arrayValue)
					{
						std::cout<<"Error undistort_intrinsic type:"<<filename<<":"<<i<<std::endl;
						is.close();
						return;
					}
					if(root["undistort_intrinsic"][i].size()!=3)
					{
						std::cout<<"Error undistort_intrinsic size:"<<filename<<":"<<i<<std::endl;
						is.close();
						return;
					}
					for(unsigned int j=0;j<root["undistort_intrinsic"][i].size();j++)
					{
						double data=root["undistort_intrinsic"][i][j].asDouble();
						intrinsic.push_back(data);
					}
				}
			}
			else if(root["undistort_intrinsic"].size()==9)
			{
				for(unsigned int i=0;i<root["undistort_intrinsic"].size();i++)
				{
					double data=root["undistort_intrinsic"][i].asDouble();
					intrinsic.push_back(data);
				}
			}
			else
			{
				std::cout<<"Error undistort_intrinsic size:"<<filename<<std::endl;
				is.close();
				return;
			}
		}
		else
		{
			std::cout<<"Error undistort_intrinsic type:"<<filename<<std::endl;
			is.close();
			return;
		}
		K<<intrinsic[0],intrinsic[1],intrinsic[2],
			intrinsic[3],intrinsic[4],intrinsic[5],
			intrinsic[6],intrinsic[7],intrinsic[8];

		//read distortion[]
		if(root["undistort_distortion"].isNull()||root["undistort_distortion"].type()!=Json::arrayValue)
		{
			std::cout<<"Error undistort_distortion type:"<<filename<<std::endl;
			is.close();
			return;
		}
		for(unsigned int i=0;i<root["undistort_distortion"].size();i++)
		{
			double data=root["undistort_distortion"][i].asDouble();
			distortion.push_back(data);
		}
		
		dist.clear();
		for(unsigned int i=0;i<distortion.size();i++)
		{
			dist.push_back(distortion[i]);
		}
	}

	is.close();
	return;
}


// #include <fstream>
// #include <stdio.h>
// #include <string>

// #include "yaml-cpp/yaml.h"

// void LoadIntrinsic(const std::string &filename,Eigen::Matrix3d &K,std::vector<double> &dist)
// {
// 	YAML::Node root=YAML::LoadFile(filename);
// 	YAML::Node CameraMat=root["CameraMat"];
// 	std::vector<double> intri=CameraMat["data"].as<std::vector<double>>();
// 	YAML::Node DistCoeff=root["DistCoeff"];
// 	int dist_col=DistCoeff["cols"].as<int>();
// 	std::vector<double> d=DistCoeff["data"].as<std::vector<double>>();
	
// 	K<<intri[0],intri[1],intri[2],
// 		intri[3],intri[4],intri[5],
// 		intri[6],intri[7],intri[8];
// 	dist.clear();
// 	for (int i=0;i<dist_col;i++)
// 	{
// 		dist.push_back(d[i]);
// 	}

// 	return;
// }