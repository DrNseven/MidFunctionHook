//==============================================================================
// CMain.h
//==============================================================================
    
//==========================================================================================================================

//////////////////////
//		CT 			//
//////////////////////


//IDF
#define ct_idf_legs	((Stride==32) && (NumVertices==2118) && (primCount==3354))
#define ct_idf_head1 ((Stride==32) && (NumVertices==1761) && (primCount==2681))
#define ct_idf_head2 ((Stride==32) && (NumVertices==1677) && (primCount==2713))
#define ct_idf_body ((Stride==32) && (NumVertices==4523) && (primCount==6700))

#define ct_idf ct_idf_legs || ct_idf_head1 || ct_idf_head2 || ct_idf_body


//SAS
#define ct_sas_legs ((Stride==32) && (NumVertices==4442) && (primCount==5475))
#define ct_sas_head ((Stride==32) && (NumVertices==1215) && (primCount==1749))
#define ct_sas_body ((Stride==32) && (NumVertices==5443) && (primCount==8008))

#define ct_sas ct_sas_legs || ct_sas_head || ct_sas_body


//FBI
#define ct_fbi_legs ((Stride==32) && (NumVertices==1646) && (primCount==2714))
#define ct_fbi_body ((Stride==32) && (NumVertices==5395) && (primCount==8657))
#define ct_fbi_head1 ((Stride==32) && (NumVertices==1459) && (primCount==2566))
#define ct_fbi_head2 ((Stride==32) && (NumVertices==2223) && (primCount==3672))
#define ct_fbi_head3 ((Stride==32) && (NumVertices==2778) && (primCount==4244))
#define ct_fbi_head4 ((Stride==32) && (NumVertices==993) && (primCount==1722))
#define ct_fbi_head5 ((Stride==32) && (NumVertices==2957) && (primCount==4234))

#define ct_fbi ct_fbi_legs || ct_fbi_body || ct_fbi_head1 || ct_fbi_head2 || ct_fbi_head3 || ct_fbi_head4 || ct_fbi_head5


//SWAT
#define ct_swat_legs ((Stride==32) && (NumVertices==3650) && (primCount==4030))
#define ct_swat_body1 ((Stride==32) && (NumVertices==6016) && (primCount==8022))
#define ct_swat_body2 ((Stride==32) && (NumVertices==5675) && (primCount==7713))
#define ct_swat_body3 ((Stride==32) && (NumVertices==6112) && (primCount==8261))
#define ct_swat_body4 ((Stride==32) && (NumVertices==6777) && (primCount==8930))
#define ct_swat_body5 ((Stride==32) && (NumVertices==6087) && (primCount==8226))
#define ct_swat_head1 ((Stride==32) && (NumVertices==1883) && (primCount==2986))
#define ct_swat_head2 ((Stride==32) && (NumVertices==1917) && (primCount==3004))
#define ct_swat_head3 ((Stride==32) && (NumVertices==1835) && (primCount==2898))
#define ct_swat_head4 ((Stride==32) && (NumVertices==1980) && (primCount==3074))
#define ct_swat_head5 ((Stride==32) && (NumVertices==1834) && (primCount==2898))

#define ct_swat ct_swat_legs || ct_swat_body1 || ct_swat_body2 || ct_swat_body3 || ct_swat_body4 || ct_swat_body5 || ct_swat_head1 || ct_swat_head2 || ct_swat_head3 || ct_swat_head4 || ct_swat_head5


//GSG9
#define ct_gsg9_legs ((Stride==32) && (NumVertices==1410) && (primCount==2352))
#define ct_gsg9_body ((Stride==32) && (NumVertices==3301) && (primCount==5424))
#define ct_gsg9_head1 ((Stride==32) && (NumVertices==2113) && (primCount==3391))
#define ct_gsg9_head2 ((Stride==32) && (NumVertices==2157) && (primCount==3461))
#define ct_gsg9_head3 ((Stride==32) && (NumVertices==2151) && (primCount==3459))

#define ct_gsg9 ct_gsg9_legs || ct_gsg9_body || ct_gsg9_head1 || ct_gsg9_head2 || ct_gsg9_head3


//GIGN
#define ct_gign_legs ((Stride==32) && (NumVertices==1258) && (primCount==1950))
#define ct_gign_body ((Stride==32) && (NumVertices==4854) && (primCount==7410))
#define ct_gign_head1 ((Stride==32) && (NumVertices==1645) && (primCount==2568))
#define ct_gign_head2 ((Stride==32) && (NumVertices==1611) && (primCount==2522))
#define ct_gign_head3 ((Stride==32) && (NumVertices==1601) && (primCount==2502))

#define ct_gign ct_gign_legs || ct_gign_body || ct_gign_head1 || ct_gign_head2 || ct_gign_head3


//SEAL
#define ct_seal_legs1 ((Stride==32) && (NumVertices==2924) && (primCount==3540))
#define ct_seal_legs2 ((Stride==32) && (NumVertices==2923) && (primCount==3540))
#define ct_seal_body1 ((Stride==32) && (NumVertices==5547) && (primCount==8003))
#define ct_seal_body2 ((Stride==32) && (NumVertices==5524) && (primCount==8106))
#define ct_seal_body3 ((Stride==32) && (NumVertices==5680) && (primCount==8166))
#define ct_seal_body4 ((Stride==32) && (NumVertices==5334) && (primCount==7910))
#define ct_seal_body5 ((Stride==32) && (NumVertices==5436) && (primCount==8003))
#define ct_seal_head1 ((Stride==32) && (NumVertices==2539) && (primCount==3527))
#define ct_seal_head2 ((Stride==32) && (NumVertices==3137) && (primCount==3948))
#define ct_seal_head3 ((Stride==32) && (NumVertices==3245) && (primCount==4158))
#define ct_seal_head4 ((Stride==32) && (NumVertices==2963) && (primCount==3792))
#define ct_seal_head5 ((Stride==32) && (NumVertices==4084) && (primCount==4697))

#define ct_seal ct_seal_legs1 || ct_seal_legs2 || ct_seal_body1 || ct_seal_body2 || ct_seal_body3 || ct_seal_body4 || ct_seal_body5 || ct_seal_head1 || ct_seal_head2 || ct_seal_head3 || ct_seal_head4 || ct_seal_head5

//CT Models
#define CT_Models (ct_idf || ct_sas || ct_fbi || ct_swat || ct_gsg9 || ct_gign || ct_seal)

//CT Heads
#define CT_Heads (ct_idf_head1 || ct_idf_head2 || ct_sas_head || ct_fbi_head1 || ct_fbi_head2 || ct_fbi_head3 || ct_fbi_head4 || ct_fbi_head5 || ct_swat_head1 || ct_swat_head2 || ct_swat_head3 || ct_swat_head4 || ct_swat_head5 || ct_gsg9_head1 || ct_gsg9_head2 || ct_gsg9_head3 || ct_gign_head1 || ct_gign_head2 || ct_gign_head3 || ct_seal_head1 || ct_seal_head2 || ct_seal_head3 || ct_seal_head4 || ct_seal_head5)


//////////////////////
//		T 			//
//////////////////////


//ELITE CREW
#define t_elite1_legs ((Stride==32) && (NumVertices==2531) && (primCount==3888))
#define t_elite1_head ((Stride==32) && (NumVertices==1134) && (primCount==2024))
#define t_elite1_body ((Stride==32) && (NumVertices==3606) && (primCount==5856))
#define t_elite2_legs ((Stride==32) && (NumVertices==1889) && (primCount==3088))
#define t_elite2_head ((Stride==32) && (NumVertices==1310) && (primCount==2302))
#define t_elite2_body ((Stride==32) && (NumVertices==3816) && (primCount==5930))
#define t_elite3_legs ((Stride==32) && (NumVertices==2416) && (primCount==3778))
#define t_elite3_head ((Stride==32) && (NumVertices==1430) && (primCount==2422))
#define t_elite3_body ((Stride==32) && (NumVertices==2587) && (primCount==4334))
#define t_elite4_legs ((Stride==32) && (NumVertices==2138) && (primCount==3424))
#define t_elite4_head ((Stride==32) && (NumVertices==1352) && (primCount==2268))
#define t_elite5_legs ((Stride==32) && (NumVertices==1986) && (primCount==3044))
#define t_elite5_head ((Stride==32) && (NumVertices==1372) && (primCount==2286))
#define t_elite5_body ((Stride==32) && (NumVertices== 3162) && (primCount==5182))


#define t_elite t_elite1_legs || t_elite1_head || t_elite1_body || t_elite2_legs || t_elite2_head || t_elite2_body || t_elite3_legs || t_elite3_head || t_elite3_body || t_elite4_legs || t_elite4_head || t_elite5_legs || t_elite5_head || t_elite5_body


//Separatist
#define t_separatist_legs ((Stride==32) && (NumVertices==2536) && (primCount==4196))
#define t_separatist_head ((Stride==32) && (NumVertices==1106) && (primCount==2018))
#define t_separatist_body ((Stride==32) && (NumVertices==3210) && (primCount==5382))

#define t_separatist t_separatist_legs || t_separatist_head || t_separatist_body


//Anarchist
#define t_anarchist_legs ((Stride==32) && (NumVertices==1671) && (primCount==2876))
#define t_anarchist_head ((Stride==32) && (NumVertices==1925) && (primCount==3314))
#define t_anarchist_body ((Stride==32) && (NumVertices==3881) && (primCount==6774))

#define t_anarchist t_anarchist_legs || t_anarchist_head || t_anarchist_body


//Professional
#define t_professional_legs ((Stride==32) && (NumVertices==2056) && (primCount==3436))
#define t_professional_body ((Stride==32) && (NumVertices==5116) && (primCount==8253))
#define t_professional_head1 ((Stride==32) && (NumVertices==927) && (primCount==1626))
#define t_professional_head2 ((Stride==32) && (NumVertices==646) && (primCount==1248))
#define t_professional_head3 ((Stride==32) && (NumVertices==1053) && (primCount==1968))
#define t_professional_head4 ((Stride==32) && (NumVertices==1197) && (primCount==2256))
#define t_professional_head5 ((Stride==32) && (NumVertices==924) && (primCount==1632))
#define t_professional_glasses1 ((Stride==32) && (NumVertices==266) && (primCount==348))
#define t_professional_glasses2 ((Stride==32) && (NumVertices==200) && (primCount==276))

#define t_professional t_professional_legs || t_professional_body || t_professional_head1 || t_professional_head2 || t_professional_head3 || t_professional_head4 || t_professional_head5 || t_professional_glasses1 || t_professional_glasses2


//Phoenix
#define t_phoenix_legs ((Stride==32) && (NumVertices==2599) && (primCount==4097))
#define t_phoenix_body ((Stride==32) && (NumVertices==2944) && (primCount==4916))
#define t_phoenix_head ((Stride==32) && (NumVertices==876) && (primCount==1630))

#define t_phoenix t_phoenix_legs || t_phoenix_body || t_phoenix_head


//Balkan
#define t_balkan_legs1 ((Stride==32) && (NumVertices==1525) && (primCount==2525))
#define t_balkan_legs2 ((Stride==32) && (NumVertices==1273) && (primCount==2113))
#define t_balkan_body ((Stride==32) && (NumVertices==5215) && (primCount==8130))
#define t_balkan_head1 ((Stride==32) && (NumVertices==1214) && (primCount==2292))
#define t_balkan_head2 ((Stride==32) && (NumVertices==1215) && (primCount==2286))
#define t_balkan_head3 ((Stride==32) && (NumVertices==1291) && (primCount==2437))
#define t_balkan_head4 ((Stride==32) && (NumVertices==1345) && (primCount==2488))
#define t_balkan_head5 ((Stride==32) && (NumVertices==1624) && (primCount==2936))

#define t_balkan t_balkan_legs1 || t_balkan_legs2 || t_balkan_body || t_balkan_head1 || t_balkan_head2 || t_balkan_head3 || t_balkan_head4 || t_balkan_head5


//Pirate
#define t_pirate_legs1 ((Stride==32) && (NumVertices==934) && (primCount==1525))
#define t_pirate_legs2 ((Stride==32) && (NumVertices==991) && (primCount==1525))
#define t_pirate_body ((Stride==32) && (NumVertices==7900) && (primCount==9248))
#define t_pirate_head1 ((Stride==32) && (NumVertices==1996) && (primCount==2906))
#define t_pirate_head2 ((Stride==32) && (NumVertices==1183) && (primCount==2045))
#define t_pirate_head3 ((Stride==32) && (NumVertices==1380) && (primCount==2493))
#define t_pirate_head4 ((Stride==32) && (NumVertices==1314) && (primCount==2367))

#define t_pirate t_pirate_legs1 || t_pirate_legs2 || t_pirate_body || t_pirate_head1 || t_pirate_head2 || t_pirate_head3 || t_pirate_head4

//T Models
#define T_Models (t_elite || t_separatist || t_anarchist || t_professional || t_phoenix || t_balkan || t_pirate)

//T Heads
#define T_Heads (t_elite1_head || t_elite2_head|| t_elite3_head||t_elite4_head||t_elite5_head || t_separatist_head || t_anarchist_head || t_professional_head1 || t_professional_head2 || t_professional_head3 || t_professional_head4 || t_professional_head5 || t_phoenix_head || t_balkan_head1 || t_balkan_head2 || t_balkan_head3 || t_balkan_head4 || t_balkan_head5 || t_pirate_head1 || t_pirate_head2 || t_pirate_head3 || t_pirate_head4)

