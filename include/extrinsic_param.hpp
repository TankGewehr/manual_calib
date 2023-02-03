#pragma once

#include <iostream>
#include"jsoncpp/json/json.h"

void LoadExtrinsic(const std::string &filename,Eigen::Matrix4d &extrinsic)
{
	Eigen::Matrix4d ori_extrinsic;
	Json::Reader reader;
	Json::Value root;
	std::vector<double> rotation;
	std::vector<double> translation;

	std::ifstream is(filename,std::ios::binary);
	if(!is.is_open())
	{
		std::cout<<"Error opening file:"<<filename<<std::endl;
		return;
	}

	if(reader.parse(is,root))
	{
		//read rotation[9] or rotation[3][3]
		if(!root["rotation"].isNull()&&root["rotation"].type()==Json::arrayValue)
		{
			if(root["rotation"].size()==3)
			{
				for(unsigned int i=0;i<root["rotation"].size();i++)
				{
					if(root["rotation"][i].isNull()||root["rotation"][i].type()!=Json::arrayValue)
					{
						std::cout<<"Error rotation type:"<<filename<<":"<<i<<std::endl;
						is.close();
						return;
					}
					if(root["rotation"][i].size()!=3)
					{
						std::cout<<"Error rotation size:"<<filename<<":"<<i<<std::endl;
						is.close();
						return;
					}
					for(unsigned int j=0;j<root["rotation"][i].size();j++)
					{
						double data=root["rotation"][i][j].asDouble();
						rotation.push_back(data);
					}

					
				}
			}
			else if(root["rotation"].size()==9)
			{
				for(unsigned int i=0;i<root["rotation"].size();i++)
				{
					double data=root["rotation"][i].asDouble();
					rotation.push_back(data);
				}
			}
			else
			{
				std::cout<<"Error rotation size:"<<filename<<std::endl;
				is.close();
				return;
			}
		}
		else
		{
			std::cout<<"Error rotation type:"<<filename<<std::endl;
			is.close();
			return;
		}

		//read translation[3] or translation{x,y,z}
		if(!root["translation"].isNull()&&root["translation"].type()==Json::arrayValue)
		{
			for(unsigned int i=0;i<root["translation"].size();i++)
			{
				double data=root["translation"][i].asDouble();
				translation.push_back(data);
			}
		}
		else if(!root["translation"].isNull()&&root["translation"].type()==Json::objectValue)
		{
			double x=root["translation"]["x"].asDouble();
			double y=root["translation"]["y"].asDouble();
			double z=root["translation"]["z"].asDouble();
			translation.push_back(x);
			translation.push_back(y);
			translation.push_back(z);
		}
		else
		{
			std::cout<<"Error translation type:"<<filename<<std::endl;
			is.close();
			return;
		}

		ori_extrinsic<<rotation[0],rotation[1],rotation[2],translation[0],
			rotation[3],rotation[4],rotation[5],translation[1],
			rotation[6],rotation[7],rotation[8],translation[2],
			0,0,0,1;

		extrinsic=ori_extrinsic.inverse();
	}

	is.close();
	return;
}


// #include <fstream>
// #include <stdio.h>
// #include <string>
// #include "yaml-cpp/yaml.h"
// void LoadExtrinsic(const std::string &filename,Eigen::Matrix4d &extrinsic)
// {
// 	YAML::Node root=YAML::LoadFile(filename);
// 	YAML::Node CameraExtrinsicMat=root["CameraExtrinsicMat"];
// 	std::vector<double> data=CameraExtrinsicMat["data"].as<std::vector<double>>();
// 	extrinsic<<data[0],data[1],data[2],data[3],
// 		data[4],data[5],data[6],data[7],
// 		data[8],data[9],data[10],data[11],
// 		data[12],data[13],data[14],data[15];

// 	return;
// }