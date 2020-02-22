  //------- pop<nn>-s-report.cxx-----------------------------------------------
  // ------ Write results into S-compatible file -- PDS July 2003   -------
  // ------ Based on work from Michael Prager
  // ------ The file will be named <name>.rdat, where <name> is the TPL file name
  // ------ The file can be read by S with the statement: x <- dget("<name>.rdat")

  const char* cc = ", ";    // To reduce clutter later on
  int i, il, y;                // Vars used as indices
  
  // Open the S output file
  ofstream sfile ((const char*)(adprogram_name + ".rdat"));

  // ------------------ START OVERALL S STRUCTURE (LIST) -------------------------

  sfile << "structure(list(";

   
  // ------------------ TIME SERIES DATA, 1963-2002 -------------------------

  // Write start of data frame for continous time series from 1963-2002
       sfile << "t.series = structure(list(" << endl;

  // Write vector of years:
     for(y=styr; y<=endyr; y++) {xdum2[y] = dvariable(y);}
      write_s_yrcol(sfile, value(xdum2), "year", styr, endyr, 0);
      
  // Write time series data (1963-2002)
      write_s_yrcol(sfile, value(rowsum(natage_f)), "numbers.f", styr, endyr, 0);
      write_s_yrcol(sfile, value(rowsum(natage_m)), "numbers.m", styr, endyr, 0);
      write_s_yrcol(sfile, value(pred_rec), "Recr", styr, endyr, 0);
      write_s_yrcol(sfile, value(spawn_biom), "spbiom", styr, endyr, 0);
      write_s_yrcol(sfile, value(Fmort_fish1+Fmort_fish3), "fmort", styr, endyr, 0);
      write_s_yrcol(sfile, value(spawn_biom/max(spawn_biom)), "Brat", styr, endyr, 0);
      write_s_yrcol(sfile, value((Fmort_fish1+Fmort_fish3)/F40), "Frat", styr, endyr, 0);
      write_s_yrcol(sfile, value(tot_biom), "totbiom", styr, endyr, 0);
      write_s_yrcol(sfile, value(pred_catch_fish1), "Catch_HAL", styr, endyr, 0);
      write_s_yrcol(sfile, value(pred_catch_fish3), "Catch_TWL", styr, endyr, 1);
      write_s_rownames_int(sfile, styr, endyr, "df", 0);
  
  // ------------------ START N-AT-AGE MATRIX -------------------------
  // Matrix of numbers at age, with ages as columns & years as rows

  write_s_matrix(sfile, value(natage_f), "natage.female", styr, endyr, 1, nages);
  write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes  COLUMN names
  write_s_matrix(sfile, value(natage_m), "natage.male", styr, endyr, 1, nages);
  write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes  COLUMN names
  
 // ---------------------------PREDICTED RECRUITMENT CURVE -------------------- -------------
 // Write start of data frame for predicted recruitment curve
      
//      sfile << "reccurve = structure(list(" << endl;     
//      write_s_yrcol(sfile, value(SRec_spawn), "Srec.spawn", 1, 20, 0);
//      write_s_yrcol(sfile, value(SRec_rec), "Srec.rec", 1, 20, 1);
//      write_s_rownames_int(sfile, 1, 20, "df", 0);

 // ------------------------------SELECTIVITY CURVES ----------------------------------------
 // write start of age based selectivity curves
    sfile << "agesel = structure(list(" << endl;
    write_s_yrcol(sfile, value(fish1_sel_f), "fish1sel.f", 1, nages, 0);
    write_s_yrcol(sfile, value(fish1_sel_m), "fish1sel.m", 1, nages, 0);
    write_s_yrcol(sfile, value(fish3_sel_f), "fish3sel.f", 1, nages, 0);
    write_s_yrcol(sfile, value(fish3_sel_m), "fish3sel.m", 1, nages, 0);
    write_s_yrcol(sfile, value(fish4_sel_f), "fish4sel.f", 1, nages, 0);
    write_s_yrcol(sfile, value(fish4_sel_m), "fish4sel.m", 1, nages, 0);
    write_s_yrcol(sfile, value(srv1_sel_f), "srv1sel.f", 1, nages, 0);
    write_s_yrcol(sfile, value(srv1_sel_m), "srv1sel.m", 1, nages, 0);
    write_s_yrcol(sfile, value(srv2_sel_f), "srv2sel.f", 1, nages, 0);
    write_s_yrcol(sfile, value(srv2_sel_m), "srv2sel.m", 1, nages, 0);
    write_s_yrcol(sfile, value(srv7_sel_f), "srv7sel.f", 1, nages, 0);
    write_s_yrcol(sfile, value(srv7_sel_m), "srv7sel.m", 1, nages, 1);
    write_s_rownames_vec(sfile, aa, 1, nages, "df", 0);
  // ------------------ age_length matrices -------------------------
  // Matrix of numbers at age, with ages as columns & years as rows
  write_s_matrix(sfile, value(sizeage_f), "sizeage.f", 1, nlenbins, 1, nages);
  write_s_rownames_vec(sfile, aa, 1, nlenbins, "ma", 0);  // this writes  COLUMN names
  write_s_matrix(sfile, value(sizeage_m), "sizeage.m", 1, nlenbins, 1, nages);
  write_s_rownames_vec(sfile, aa, 1, nlenbins, "ma", 0);  // this writes  COLUMN names
  write_s_matrix(sfile, value(sizeage_f_new), "sizeage.fnew", 1, nlenbins, 1, nages);
  write_s_rownames_vec(sfile, aa, 1, nlenbins, "ma", 0);  // this writes  COLUMN names
  write_s_matrix(sfile, value(sizeage_m_new), "sizeage.mnew", 1, nlenbins, 1, nages);
  write_s_rownames_vec(sfile, aa, 1, nlenbins, "ma", 0);  // this writes  COLUMN names
  
// ------------------------------growth and maturity curves ----------------------------------------
 // write start of age based selectivity curves
    sfile << "growthmat = structure(list(" << endl;
    write_s_yrcol(sfile, wt_f, "wt.f", 1, nages, 0);
    write_s_yrcol(sfile, wt_m, "wt.m", 1, nages, 0);
    write_s_yrcol(sfile, p_mature, "mage", 1, nages, 1);
    write_s_rownames_vec(sfile, aa, 1, nages, "df", 0);
 
 // ------------------ CPUE TIME SERIES DATA, 1968-1979 -------------------------
 //     sfile << "obscpue = structure(list(" << endl;
 //     write_s_yrcol(sfile, value(obs_cpue), "obscpue", 1, nyrs_cpue, 0);
 //     write_s_yrcol(sfile, value(pred_cpue), "predcpue", 1, nyrs_cpue, 1);
 //     write_s_rownames_vec(sfile, yrs_cpue, 1, nyrs_cpue, "df", 0);
 

 // ------------------ OBSERVED TRAWL SURVEY TIME SERIES DATA, 1982-2002 -------------------------
        sfile << "obssrv1 = structure(list(" << endl;
        write_s_yrcol(sfile,   (obs_srv1_biom), "obssrv1", 1, nyrs_srv1, 0);
        write_s_yrcol(sfile,   (obs_srv1_lci), "obssrv1.lci", 1, nyrs_srv1, 0);
        write_s_yrcol(sfile,   (obs_srv1_uci), "obssrv1.uci", 1, nyrs_srv1, 0);
        write_s_yrcol(sfile, value(pred_srv1(yrs_srv1)), "predsrv1",1,nyrs_srv1, 1);
        write_s_rownames_vec(sfile, yrs_srv1, 1, nyrs_srv1, "df", 0);
   
        sfile << "obssrv2 = structure(list(" << endl;
        write_s_yrcol(sfile,   (obs_srv2_biom), "obssrv2", 1, nyrs_srv2, 0);
        write_s_yrcol(sfile,   (obs_srv2_lci), "obssrv2.lci", 1, nyrs_srv2, 0);
        write_s_yrcol(sfile,   (obs_srv2_uci), "obssrv2.uci", 1, nyrs_srv2, 0);
        write_s_yrcol(sfile, value(pred_srv2(yrs_srv2)), "predsrv2",1,nyrs_srv2, 1);
        write_s_rownames_vec(sfile, yrs_srv2, 1, nyrs_srv2, "df", 0);
    
       sfile << "obssrv3 = structure(list(" << endl;
        write_s_yrcol(sfile,   (obs_srv3_biom), "obssrv3", 1, nyrs_srv3, 0);
        write_s_yrcol(sfile,   (obs_srv3_lci), "obssrv3.lci", 1, nyrs_srv3, 0);
        write_s_yrcol(sfile,   (obs_srv3_uci), "obssrv3.uci", 1, nyrs_srv3, 0);
        write_s_yrcol(sfile, value(pred_srv3(yrs_srv3)), "predsrv3",1,nyrs_srv3, 1);
        write_s_rownames_vec(sfile, yrs_srv3, 1, nyrs_srv3, "df", 0);
    
     sfile << "obssrv4 = structure(list(" << endl;
        write_s_yrcol(sfile,   (obs_srv4_biom), "obssrv4", 1, nyrs_srv4, 0);
        write_s_yrcol(sfile,   (obs_srv4_lci), "obssrv4.lci", 1, nyrs_srv4, 0);
        write_s_yrcol(sfile,   (obs_srv4_uci), "obssrv4.uci", 1, nyrs_srv4, 0);
        write_s_yrcol(sfile, value(pred_srv4(yrs_srv4)), "predsrv4",1,nyrs_srv4, 1);
        write_s_rownames_vec(sfile, yrs_srv4, 1, nyrs_srv4, "df", 0);
     
     sfile << "obssrv5 = structure(list(" << endl;
        write_s_yrcol(sfile,   (obs_srv5_biom), "obssrv5", 1, nyrs_srv5, 0);
        write_s_yrcol(sfile,   (obs_srv5_lci), "obssrv5.lci", 1, nyrs_srv5, 0);
        write_s_yrcol(sfile,   (obs_srv5_uci), "obssrv5.uci", 1, nyrs_srv5, 0);
        write_s_yrcol(sfile, value(pred_srv5(yrs_srv5)), "predsrv5",1,nyrs_srv5, 1);
        write_s_rownames_vec(sfile, yrs_srv5, 1, nyrs_srv5, "df", 0);
 
     sfile << "obssrv6 = structure(list(" << endl;
        write_s_yrcol(sfile,   (obs_srv6_biom), "obssrv6", 1, nyrs_srv6, 0);
        write_s_yrcol(sfile,   (obs_srv6_lci), "obssrv6.lci", 1, nyrs_srv6, 0);
        write_s_yrcol(sfile,   (obs_srv6_uci), "obssrv6.uci", 1, nyrs_srv6, 0);
        write_s_yrcol(sfile, value(pred_srv6(yrs_srv6)), "predsrv6",1,nyrs_srv6, 1);
        write_s_rownames_vec(sfile, yrs_srv6, 1, nyrs_srv6, "df", 0);
        
     sfile << "obssrv7 = structure(list(" << endl;
        write_s_yrcol(sfile,   (obs_srv7_biom), "obssrv7", 1, nyrs_srv7, 0);
        write_s_yrcol(sfile,   (obs_srv7_lci), "obssrv7.lci", 1, nyrs_srv7, 0);
        write_s_yrcol(sfile,   (obs_srv7_uci), "obssrv7.uci", 1, nyrs_srv7, 0);
        write_s_yrcol(sfile, value(pred_srv7(yrs_srv7)), "predsrv7",1,nyrs_srv7, 1);
        write_s_rownames_vec(sfile, yrs_srv7, 1, nyrs_srv7, "df", 0);
    
 // stopper
   
 // ----------------------------AGE AND LENGTH COMPOSITIONS ----------------------------------------
 // write start of age composition matrices

 // fishery biased ages
 //   write_s_imatrix(sfile, value(oac_fish_biased), yrs_fish_biased_ac, "oac.f.biased", 1,nyrs_fish_biased_ac, 1, nages);
 //   write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes COLUMN names 

 //   write_s_matrix(sfile, value(eac_fish_biased), "eac.f.biased", styr_fish,endyr, 1, nages);
 //   write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes COLUMN names

// fishery unbiased ages
    write_s_imatrix(sfile, value(oac_fish1), yrs_fish1_age, "oac.fish1", 1,nyrs_fish1_age, 1, nages);
    write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes COLUMN names 

    write_s_imatrix(sfile, value(eac_fish1), yrs_fish1_age, "eac.fish1", 1,nyrs_fish1_age,1 ,nages);
    write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes COLUMN names	
    
// survey ages
    write_s_imatrix(sfile, value(oac_srv1), yrs_srv1_age, "oac.srv1", 1,nyrs_srv1_age, 1, nages);
    write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes COLUMN names

     write_s_imatrix(sfile, value(eac_srv1), yrs_srv1_age, "eac.srv1", 1,nyrs_srv1_age, 1, nages);
    write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(oac_srv2), yrs_srv2_age, "oac.srv2", 1,nyrs_srv2_age, 1, nages);
    write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes COLUMN names

     write_s_imatrix(sfile, value(eac_srv2), yrs_srv2_age, "eac.srv2", 1,nyrs_srv2_age, 1, nages);
    write_s_rownames_vec(sfile, aa, 1, nages, "ma", 0);  // this writes COLUMN names

//  fishery lengths
    write_s_imatrix(sfile, value(osc_fish1_f), yrs_fish1_size, "olc.fish1.f", 1,nyrs_fish1_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_fish1_f), yrs_fish1_size, "elc.fish1.f", 1,nyrs_fish1_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(osc_fish1_m), yrs_fish1_size, "olc.fish1.m", 1,nyrs_fish1_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_fish1_m), yrs_fish1_size, "elc.fish1.m", 1,nyrs_fish1_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(osc_fish3_f), yrs_fish3_size, "olc.fish3.f", 1,nyrs_fish3_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_fish3_f), yrs_fish3_size, "elc.fish3.f", 1,nyrs_fish3_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(osc_fish3_m), yrs_fish3_size, "olc.fish3.m", 1,nyrs_fish3_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_fish3_m), yrs_fish3_size, "elc.fish3.m", 1,nyrs_fish3_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

//  survey lengths
    write_s_imatrix(sfile, value(osc_srv1_f), yrs_srv1_size, "olc.srv1.f", 1,nyrs_srv1_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_srv1_f), yrs_srv1_size, "elc.srv1.f", 1,nyrs_srv1_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(osc_srv1_m), yrs_srv1_size, "olc.srv1.m", 1,nyrs_srv1_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_srv1_m), yrs_srv1_size, "elc.srv1.m", 1,nyrs_srv1_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(osc_srv2_f), yrs_srv2_size, "olc.srv2.f", 1,nyrs_srv2_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_srv2_f), yrs_srv2_size, "elc.srv2.f", 1,nyrs_srv2_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(osc_srv2_m), yrs_srv2_size, "olc.srv2.m", 1,nyrs_srv2_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_srv2_m), yrs_srv2_size, "elc.srv2.m", 1,nyrs_srv2_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(osc_srv7_f), yrs_srv7_size, "olc.srv7.f", 1,nyrs_srv7_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_srv7_f), yrs_srv7_size, "elc.srv7.f", 1,nyrs_srv7_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(osc_srv7_m), yrs_srv7_size, "olc.srv7.m", 1,nyrs_srv7_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names

    write_s_imatrix(sfile, value(esc_srv7_m), yrs_srv7_size, "elc.srv7.m", 1,nyrs_srv7_size, 1, nlenbins);
    write_s_rownames_vec(sfile, len_bin_labels, 1, nlenbins, "ma", 0);  // this writes COLUMN names
 
 
//-----------EFFECTIVE N BY YEAR ---------------------------------------------------------------
//	sfile << "effn = structure(list(" << endl;
//	write_s_yrcol(sfile, value(effn(1)), "ac.f.biased", styr, endyr, 0);
//	write_s_yrcol(sfile, value(effn(2)), "ac.f.unbiased", styr, endyr, 0);
// 	write_s_yrcol(sfile, value(effn(3)), "lc.f", styr, endyr, 0);
// 	write_s_yrcol(sfile, value(effn(4)), "ac.s.", styr, endyr, 0);
// 	write_s_yrcol(sfile, value(effn(5)), "lc.s", styr, endyr, 1);
//	write_s_rownames_int(sfile, styr, endyr, "df", 0);

  // ------------------ START LIKELIHOOD COMPONENTS VECTOR -------------------------
  // The vector of likelihood components will be stored as an S numeric vector.

  // Write start of likelihood components vector:
      sfile << "likecomp = structure(c(";
      sfile << age_like(1) << cc << age_like(2) << cc << age_like(3) << cc << age_like(4) << cc << age_like(5) << cc << age_like(6) << cc << age_like(7) << cc << age_like(8) << cc << age_like(9) << cc << age_like(10) << cc << age_like(11) << cc << age_like(12) << cc << age_like(13) << cc << age_like(14) << cc << surv_like(1) << cc<<surv_like(2) << cc<<surv_like(3) << cc<<surv_like(4) << cc<<surv_like(5) << cc<<surv_like(6) << cc<<surv_like(7) << cc<<surv_like(8) <<cc<<obj_fun;
        sfile << ")," << endl; 
        sfile << ".Names = c('L.fish1age','L.surv1age','L.fish1sizef','L.fish1sizem','L.fish2size','L.fish3sizef','L.fish3sizem','L.fish4size','L.surv1sizef','L.surv1sizem','L.surv2sizef','L.surv2sizem','L.surv7sizef','L.surv7sizem','L.surv1','L.surv2','L.surv3','L.surv4','L.surv5','L.surv6','L.surv7','L.surv8','obj.fun'";
         sfile << "))," << endl;   // Close vector of parameter values:

  //Write likelihood component values:
   //   sfile << sum(rec_like) << cc <<surv_like(2) << cc << surv_like(1) << cc;  
   //   sfile << catch_like << cc << fpen << cc << age_like(1) << cc;
   //   sfile << age_like(2) << cc << age_like(3) << cc << age_like(4) << cc;
   //   sfile << age_like(5) <<cc;
   //   sfile << ")," << endl; 

   // write some parameter values
        sfile << "parameters = structure(c(";
        sfile << q_srv1 << cc << q_srv2 << cc<< q_srv3 << cc<< q_srv4 << cc<< q_srv5 << cc<< q_srv6 << cc<< q_srv7 << cc<< q_srv8 << cc << sigr<< cc << natmort << cc<<F40<<cc<<F50;
        sfile << ")," << endl; 
        sfile << ".Names = c('q1','q2','q3','q4','q5','q6','q7','q8','sigr','natmort','F40','F50'";
         sfile << "))" << endl;   // Close vector of parameter values:

  //Write likelihood component values:
   //   sfile << sum(rec_like) << cc <<surv_like(2) << cc << surv_like(1) << cc;  
   //   sfile << catch_like << cc << fpen << cc << age_like(1) << cc;
   //   sfile << age_like(2) << cc << age_like(3) << cc << age_like(4) << cc;
   //   sfile << age_like(5) <<cc;

  //Write names of likelihood components:
  //    sfile << "'cpue.like','catch.like','Fmortpen','fish.biased.ac',";
  //    sfile << "'fish.unbiased.ac','fish.lc','aisrv.ac','aisrv.lc',"<< endl;

// ------------------ START MEAN SAMPLE WEIGHTS VECTOR -------------------------
  // The vector of mean sample weights for the age and length comps will be stored as an S numeric vector.

  // Write start of vector:
//      sfile << "avgsampwts = structure(c(";

  //Write the values:
//      sfile << sum(fish_biased_ac_samp)/nyrs_fish_biased_ac << cc;
//      sfile << sum(fish_unbiased_ac_samp)/nyrs_fish_unbiased_ac << cc;
//      sfile << sum(fish_lc_samp)/nyrs_fish_lc << cc;
//      sfile << sum(surv3_unbiased_ac_samp)/nyrs_surv3_unbiased_ac << cc;
//      sfile << sum(surv3_lc_samp)/nyrs_surv3_lc << cc;
//      sfile << ")," << endl; 

  //Write names:
//      sfile << ".Names = c('ac.fish.biased','ac.fish.unbiased','lc.f','ac.s','lc.s'"<< endl;
//      sfile << "))," << endl;   // Close vector of parameter values:

// ------------------ START RMSE VECTOR -------------------------
  // The vector of root mean square error for the reccruitment and survey data will be stored as an S numeric vector.

  // Write start of vector:
//      sfile << "rmse = structure(c(";

  //Write the values:
//      sfile << rmse(1) << cc;
//      sfile << rmse(2) << cc;
 //     sfile << rmse(3) << cc;
 //     sfile << ")," << endl; 

  //Write names:
//      sfile << ".Names = c('cpue','aisrv','rec'"<< endl;
//      sfile << "))," << endl;   // Close vector of parameter values:

  //-------- Write close of overall S list structure:--------------------------------------------
  // This is the closing punctuation plus the names of the constituent elements of the list

    sfile << "))" << endl;   // Close 
  
//  sfile << "), .Names = c('t.series'";
//  sfile << "))" << endl;

  //-------- END OF CXX FILE --------------------------------------------
