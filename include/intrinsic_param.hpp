#pragma once

#include <iostream>
#include"jsoncpp/json/json.h"

void LoadIntrinsic(const std::string &filename,Eigen::Matrix3d &K,std::vector<double> &dist,bool undistorted=true)
{
	Json::Reader reader;
	Json::Value root;
	std::vector<double> intrinsic;
	std::vector<double> distortion;
	const std::string intrinsic_key=undistorted?"undistort_intrinsic":"intrinsic";
	const std::string distortion_key=undistorted?"undistort_distortion":"distortion";

	std::ifstream is(filename,std::ios::binary);
	if(!is.is_open())
	{
		std::cout<<"Error opening file:"<<filename<<std::endl;
		return;
	}

	if(reader.parse(is,root))
	{
		//read intrinsic[9] or intrinsic[3][3]
		if(!root[intrinsic_key].isNull()&&root[intrinsic_key].type()==Json::arrayValue)
		{
			if(root[intrinsic_key].size()==3)
			{
				for(unsigned int i=0;i<root[intrinsic_key].size();i++)
				{
					if(root[intrinsic_key][i].isNull()||root[intrinsic_key][i].type()!=Json::arrayValue)
					{
						std::cout<<"Error "<<intrinsic_key<<" type:"<<filename<<":"<<i<<std::endl;
						is.close();
						return;
					}
					if(root[intrinsic_key][i].size()!=3)
					{
						std::cout<<"Error "<<intrinsic_key<<" size:"<<filename<<":"<<i<<std::endl;
						is.close();
						return;
					}
					for(unsigned int j=0;j<root[intrinsic_key][i].size();j++)
					{
						double data=root[intrinsic_key][i][j].asDouble();
						intrinsic.push_back(data);
					}
				}
			}
			else if(root[intrinsic_key].size()==9)
			{
				for(unsigned int i=0;i<root[intrinsic_key].size();i++)
				{
					double data=root[intrinsic_key][i].asDouble();
					intrinsic.push_back(data);
				}
			}
			else
			{
				std::cout<<"Error "<<intrinsic_key<<" size:"<<filename<<std::endl;
				is.close();
				return;
			}
		}
		else
		{
			std::cout<<"Error "<<intrinsic_key<<" type:"<<filename<<std::endl;
			is.close();
			return;
		}
		K<<intrinsic[0],intrinsic[1],intrinsic[2],
			intrinsic[3],intrinsic[4],intrinsic[5],
			intrinsic[6],intrinsic[7],intrinsic[8];

		//read distortion[]
		if(root[distortion_key].isNull()||root[distortion_key].type()!=Json::arrayValue)
		{
			std::cout<<"Error "<<distortion_key<<" type:"<<filename<<std::endl;
			is.close();
			return;
		}
		for(unsigned int i=0;i<root[distortion_key].size();i++)
		{
			double data=root[distortion_key][i].asDouble();
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