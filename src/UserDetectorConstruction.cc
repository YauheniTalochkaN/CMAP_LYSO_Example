#include "UserDetectorConstruction.hh"

#define SIZE(x) (size_t)(sizeof(x)/sizeof(*x))

UserDetectorConstruction::UserDetectorConstruction() : DetectorConstruction()
{

}

UserDetectorConstruction::~UserDetectorConstruction() 
{

}

void UserDetectorConstruction::BuildGeometry() 
{   
	TGeoManager* geom = RunManager::getInstance()->GetTGeoManager();

	TGeoMedium *med_vac = new TGeoMedium("Vacuum", 1, new TGeoMaterial("Vacuum", 0, 0, 0));
	TGeoMedium *med_sample = new TGeoMedium("Crystal", 2, new TGeoMaterial("Crystal", 0, 0, 0));

	TGeoVolume *top = geom->MakeBox("World", med_vac, geo_size_factor * 300.0 * unit_mkm, geo_size_factor * 300.0 * unit_mkm, geo_size_factor * 300.0 * unit_mkm);
	geom->SetTopVolume(top);
	top->SetLineColor(kMagenta);
	AddPhysicalVolume(top, BuildProperties("Air"));

	TGeoVolume *sample = geom->MakeBox("Crystal", med_sample, geo_size_factor * 290.0 * unit_mkm, geo_size_factor * 290.0 * unit_mkm, geo_size_factor * 290.0 * unit_mkm);
	sample->SetLineColor(kGreen);
	top->AddNodeOverlap(sample, 1, new TGeoTranslation(geo_size_factor * 0.0, geo_size_factor * 0.0, geo_size_factor * 0.0));
	AddPhysicalVolume(sample, BuildProperties("Lu1.6Y0.4SiO5"));

	geom->CloseGeometry();
	geom = nullptr;
}

MaterialProperties* UserDetectorConstruction::BuildProperties(const TString & name)
{
	MaterialProperties* mp = new MaterialProperties();
	
	TString folder = "../data/";

	if(name == "Lu1.6Y0.4SiO5")
	{
	    folder += name;

	    mp->SetBandGap(7.292 * unit_eV);
	    mp->SetDielectricPermittivity(10.4);
	    mp->SetUnitCellVolume(843.374 * pow(unit_A, 3.0));
	
	    mp->SetEffectiveMass(new Container("e-", LinearInterpolation::Initialization(folder + TString("/EffMass_e.txt"), unit_eV, const_me)));
	    mp->SetEffectiveMass(new Container("h", LinearInterpolation::Initialization(folder + TString("/EffMass_h.txt"), unit_eV, const_me)));

	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/O2pSi3pLu4f_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/O1s_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/O2s_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Si1s_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Si2ps_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Lu1s_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Lu2ps_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Lu3dps_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Lu4dps_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Lu5ps_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Y1s_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Y2ps_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Y3dps_IMFP.txt"), unit_eV, unit_nm), nullptr));
	    mp->SetInelasticMeanFreePath(new Container_imfp("e-", LinearInterpolation::Initialization(folder + TString("/imfp_e/Y4ps_IMFP.txt"), unit_eV, unit_nm), nullptr));

	    Double_t LO_1_em_momentum_vs_energy_x[] = {0, const_hr * M_PI/9.5/unit_A};
	    Double_t LO_1_em_momentum_vs_energy_y[] = {40.0 * unit_meV, 40.0 * unit_meV};

	    mp->SetThermalAverageInteractionTime(new Container_ait("e-", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_PLO_em_e.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_PLO_em_e.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LO_1_em_momentum_vs_energy_x, LO_1_em_momentum_vs_energy_y, SIZE(LO_1_em_momentum_vs_energy_x))));
	    mp->SetThermalAverageInteractionTime(new Container_ait("h", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_PLO_em_h.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_PLO_em_h.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LO_1_em_momentum_vs_energy_x, LO_1_em_momentum_vs_energy_y, SIZE(LO_1_em_momentum_vs_energy_x))));     
	    mp->SetThermalAverageInteractionTime(new Container_ait("ex", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_PLO_em_h.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_PLO_em_h.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LO_1_em_momentum_vs_energy_x, LO_1_em_momentum_vs_energy_y, SIZE(LO_1_em_momentum_vs_energy_x))));     

	    Double_t LO_1_abs_momentum_vs_energy_x[] = {0, const_hr * M_PI/9.5/unit_A};
	    Double_t LO_1_abs_momentum_vs_energy_y[] = {-40.0 * unit_meV, -40.0 * unit_meV};

	    mp->SetThermalAverageInteractionTime(new Container_ait("e-", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_PLO_abs_e.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_PLO_abs_e.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LO_1_abs_momentum_vs_energy_x, LO_1_abs_momentum_vs_energy_y, SIZE(LO_1_abs_momentum_vs_energy_x))));
	    mp->SetThermalAverageInteractionTime(new Container_ait("h", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_PLO_abs_h.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_PLO_abs_h.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LO_1_abs_momentum_vs_energy_x, LO_1_abs_momentum_vs_energy_y, SIZE(LO_1_abs_momentum_vs_energy_x))));     
	    mp->SetThermalAverageInteractionTime(new Container_ait("ex", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_PLO_abs_h.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_PLO_abs_h.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LO_1_abs_momentum_vs_energy_x, LO_1_abs_momentum_vs_energy_y, SIZE(LO_1_abs_momentum_vs_energy_x))));     

	    Double_t LA_1_em_momentum_vs_energy_x[] = {0, const_hr * M_PI/9.5/unit_A};
	    Double_t LA_1_em_momentum_vs_energy_y[] = {0, 7.5 * unit_meV};

	    mp->SetThermalAverageInteractionTime(new Container_ait("e-", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_DLA_em_e.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_DLA_em_e.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LA_1_em_momentum_vs_energy_x, LA_1_em_momentum_vs_energy_y, SIZE(LA_1_em_momentum_vs_energy_x))));
	    mp->SetThermalAverageInteractionTime(new Container_ait("h", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_DLA_em_h.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_DLA_em_h.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LA_1_em_momentum_vs_energy_x, LA_1_em_momentum_vs_energy_y, SIZE(LA_1_em_momentum_vs_energy_x))));     
	    mp->SetThermalAverageInteractionTime(new Container_ait("ex", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_DLA_em_h.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_DLA_em_h.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LA_1_em_momentum_vs_energy_x, LA_1_em_momentum_vs_energy_y, SIZE(LA_1_em_momentum_vs_energy_x))));     

	    Double_t LA_1_abs_momentum_vs_energy_x[] = {0, const_hr * M_PI/9.5/unit_A};
	    Double_t LA_1_abs_momentum_vs_energy_y[] = {0, -7.5 * unit_meV};

	    mp->SetThermalAverageInteractionTime(new Container_ait("e-", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_DLA_abs_e.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_DLA_abs_e.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LA_1_abs_momentum_vs_energy_x, LA_1_abs_momentum_vs_energy_y, SIZE(LA_1_abs_momentum_vs_energy_x))));
	    mp->SetThermalAverageInteractionTime(new Container_ait("h", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_DLA_abs_h.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_DLA_abs_h.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LA_1_abs_momentum_vs_energy_x, LA_1_abs_momentum_vs_energy_y, SIZE(LA_1_abs_momentum_vs_energy_x))));     
	    mp->SetThermalAverageInteractionTime(new Container_ait("ex", LinearInterpolation::Initialization(folder + TString("/phait/PhAIT_DLA_abs_h.txt"), unit_eV, unit_s), LinearInterpolation2D::Initialization(folder + TString("/phait/MLS_DLA_abs_h.txt"), unit_eV, const_hr/unit_m, 1), new LinearInterpolation(LA_1_abs_momentum_vs_energy_x, LA_1_abs_momentum_vs_energy_y, SIZE(LA_1_abs_momentum_vs_energy_x))));

	    mp->SetDensityOfStates(LinearInterpolation::Initialization(folder + TString("/DOS.txt"), unit_eV, 1.0/unit_eV));

	    CenterProperties* Ce3p = new CenterProperties("Ce3+");
	    shell* up2F5sl2 = new shell("2F5/2", 0.0 * unit_eV);
	    std::pair<TString,Double_t> nonrad_tau_2F7sl2[] = {std::make_pair("2F5/2", 1.0 * unit_ps)};
	    shell* up2F7sl2 = new shell("2F7/2", 0.25 * unit_eV, nullptr, 0, nonrad_tau_2F7sl2, 1);
	    std::pair<TString,Double_t> rad_tau_5d1[] = {std::make_pair("2F7/2", 68.0 * unit_ns), std::make_pair("2F5/2", 97.14 * unit_ns)};
	    std::pair<TString,Double_t> nonrad_tau_5d1[] = {std::make_pair("2F7/2", 1000.0 * unit_ns)};
	    shell* up5d1 = new shell("5d1", 2.9 * unit_eV, rad_tau_5d1, 2, nonrad_tau_5d1, 1);
	    Ce3p->SetLevel(up2F5sl2);
	    Ce3p->SetLevel(up2F7sl2);
	    Ce3p->SetLevel(up5d1);
	    Ce3p->SetGroundState("2F5/2");
	    Double_t Ce3p_crate_of_ex_to_5d1_en[] = {0, 1.0 * unit_eV};
	    Double_t Ce3p_crate_of_ex_to_5d1_rate[] = {0.1 / unit_ps, 0.1 / unit_ps};
	    Ce3p->SetCaptureRate(new Container_ccr("ex", "Ce3+", "5d1", new LinearInterpolation(Ce3p_crate_of_ex_to_5d1_en, Ce3p_crate_of_ex_to_5d1_rate, 2)));
	    mp->SetCenterProperties(Ce3p);
	    up2F5sl2 = nullptr;
	    up2F7sl2 = nullptr;
	    up5d1 = nullptr;
	    Ce3p = nullptr;

	    CenterProperties* e_trap = new CenterProperties("e-_trap");
	    shell* etrap_level_1 = new shell("level_1", 6.0*unit_eV);
	    std::pair<TString,Double_t> nonrad_tau_etrap_level_2[] = {std::make_pair("level_1", 1.0 * unit_ps)};
	    shell* etrap_level_2 = new shell("level_2", 7.0*unit_eV, nullptr, 0, nonrad_tau_etrap_level_2, 1);
	    e_trap->SetLevel(etrap_level_1);
	    e_trap->SetLevel(etrap_level_2);
	    e_trap->SetGroundState("level_1");
	    Double_t etrap_crate_of_e_to_level_2_en[] = {0, 1.0 * unit_eV};
	    Double_t etrap_crate_of_e_to_level_2_rate[] = {0.1 / unit_ps, 0.1 / unit_ps};
	    e_trap->SetCaptureRate(new Container_ccr("e-", "e-_trap", "level_2", new LinearInterpolation(etrap_crate_of_e_to_level_2_en, etrap_crate_of_e_to_level_2_rate, 2)));
	    mp->SetCenterProperties(e_trap);
	    etrap_level_1 = nullptr;
	    etrap_level_2 = nullptr;
	    e_trap = nullptr;

	    CenterProperties* h_trap = new CenterProperties("h_trap");
	    shell* htrap_level_1 = new shell("level_1", 1.0*unit_eV);
	    std::pair<TString,Double_t> nonrad_tau_htrap_level_2[] = {std::make_pair("level_1", 1.0 * unit_ps)};
	    shell* htrap_level_2 = new shell("level_2", 0.5*unit_eV, nullptr, 0, nonrad_tau_htrap_level_2, 1);
	    h_trap->SetLevel(htrap_level_1);
	    h_trap->SetLevel(htrap_level_2);
	    h_trap->SetGroundState("level_1");
	    Double_t htrap_crate_of_h_to_level_2_en[] = {0, 1.0 * unit_eV};
	    Double_t htrap_crate_of_h_to_level_2_rate[] = {0.1 / unit_ps, 0.1 / unit_ps};
	    h_trap->SetCaptureRate(new Container_ccr("h", "h_trap", "level_2", new LinearInterpolation(htrap_crate_of_h_to_level_2_en, htrap_crate_of_h_to_level_2_rate, 2)));
	    mp->SetCenterProperties(h_trap);
	    htrap_level_1 = nullptr;
	    htrap_level_2 = nullptr;
	    h_trap = nullptr;        
	}

	return mp;
}