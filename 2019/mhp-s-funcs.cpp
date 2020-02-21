   // mhp-s-funcs.cpp
   // This file has C++ functions for use in writing S-compatible data output.
   //===========================================================================================
   void write_s_yrcol(ofstream& sfile, const dvector& xx, const char* xname, const int& ystart,
      const int& yend, const int& lastx)
   {
      // ADMB FUNCTION to write a vector as part of an S data frame
      // MHP  -- December, 2002
      //
      // ----------Arguments----------
      // sfile    handle (object) for output file.
      // xx       vector of data to be written.
      // xname    character string to be written as S column name
      // ystart   first index of longest vector in this data frame
      // yend     last  index of longest vector in this data frame
      // lastx    set this to 1 if this is last vector in d.f., 0 otherwise
      //
      // Define limits of the vector being written
      const int ja = (xx).indexmin();
      const int jz = (xx).indexmax();
      // Write S code for vector start:
      sfile << xname << " = c(";
      // Write the data:
      for(int y=ystart; y<=yend; y++)
      {
         if(y<ja || y>jz)        // ( If out of range
            {sfile << "NA";}     // ( write NA
         else
            {sfile << xx[y];}    // If in range, write data
         if(y==yend)
            {sfile << ")";}      // ( Write appropriate punctuation
         else                    // ( to separate or terminate the
            {sfile << ", ";}     // ( values in the vector.
       }
       if(lastx>0)
         {sfile << ")," << endl;} // ( Write appropriate punctuation
       else                       // ( to separate vectors or to
         {sfile << ", " << endl;} // ( terminate the collection of vectors
       return;
   }
   //===========================================================================================
   void write_s_lencol(ofstream& sfile, const dvector& xx, const char* xname, const int& lastx)
   {
      // C++ function for ADMB to write a vector as part of an S data frame
      // This function works well for all length or age vectors or any other vectors
      // that are all complete from first to last indices.
      //
      // M. H. Prager, December 2002
      //
      // ----------Arguments----------
      // sfile    handle (object) for output file.
      // xx       vector of data to be written.
      // xname    character string to be written as S column name
      // lastx    set this to 1 if this is last vector in d.f., 0 otherwise
      //
      //  THIS ASSUMES ALL VECTORS IN THE DATA FRAME REFER TO THE SAME SET OF LENGTHS OR AGES
      //
      //
      // Define limits of the vector being written
      const int ja = (xx).indexmin();
      const int jz = (xx).indexmax();
      // Write S code for vector start:
      sfile << xname << " = c(";
      // Write the data:
      for(int j=ja; j<=jz; j++)
      {
         {sfile << xx[j];}       // Write a datum
         if(j==jz)
            {sfile << ")";}      // ( Write appropriate punctuation
         else                    // ( to separate or terminiate the
            {sfile << ", ";}     // ( values of the vector.
      }
      if(lastx>0)
         {sfile << ")," << endl;} // ( Write appropriate punct
      else                        // ( to separate vectors or to
         {sfile << ", " << endl;} // ( terminate the collection of vectors
      return;
   }
   //===========================================================================================
   // NOTE: Two functions follow to write row names for S data frames or column names for
   // S matrices
   //===========================================================================================
   void write_s_rownames_int(ofstream& sfile, const int& ia, const int& iz, const char* mtype, const int& iflast)
   {
      // C++ function for ADMB. Writes the row names as part of writing an S data frame.
      // Or writes the COLUMN NAMES as part of an S matrix.
      // This function assumes the names are consecutive integer values, as when the
      // row names are years (or possibly consecutive age classes).
      //
      // M. H. Prager, December 2002
      //
      // ----------Arguments----------
      // sfile    Object of type ofstream to hold output.
      // ia       Integer, becomes first rowname
      // iz       Integer, becomes last rowname
      // mtype    string, use "ma" for matrix, "df" for data frame
      // iflast   Set to 1 if last item in S structure, 0 if not.

      int irow;

      // Heading info
      if (strcmp(mtype,"df")==0)   // write ending for data frame
         sfile << "row.names = c(";
      else
         sfile << "c(";

      // Actual row names
      for(irow=ia; irow<=iz; irow++)
      {
         sfile << "'" << irow << "'";
         if (irow != iz)  {sfile << ",";}
         else             {sfile << ")";}
      }
      // Ending info
      if (strcmp(mtype,"df")==0)   // write ending for data frame
      {
         // cout << "\n*** BRANCHING FOR DATA FRAME ***\n";
         sfile << ", class = 'data.frame')";
      }
      else  // write ending for matrix
      {
         // cout << "\n*** BRANCHING FOR MATRIX ***\n";
         sfile << "))";
      }
      if(iflast==0) sfile << ",";  // add comma if NOT last item in surrounding structure
      sfile << endl;
      return;
   }

   //-------------------------------------------------------------------------------------------
   void write_s_rownames_vec(ofstream& sfile, const dvector& xx, const int& ia, const int& iz,
      const char* mtype, const int& iflast)
   {
      // C++ function for ADMB to write the row names as part of writing an S data frame.
      // This function assumes the row names are in a floating-point array that can be
      // indexed by consecutive integer values, as when the row names are length bins.
      //
      // M. H. Prager, December 2002
      //
      // ----------Arguments----------
      // sfile    Object of type ofstream to hold output.
      // xx       The vector of values to become the rownames
      // ia       Integer, becomes first rowname
      // iz       Integer, becomes last rowname
      // mtype    string, use "ma" for matrix, "df" for data frame
      // iflast   Set to 1 if last item in S structure, 0 if not.

      int irow;

      // Heading info
      if (strcmp(mtype,"df")==0)   // write ending for data frame
         sfile << "row.names = c(";
      else
         sfile << "c(";

      // Actual row names
      for(irow=ia; irow<=iz; irow++)
      {
         sfile << "'" << xx[irow] << "'";
         if (irow != iz)  {sfile << ",";}
         else             {sfile << ")";}
      }
      // Ending info
      if (strcmp(mtype,"df")==0)   // write ending for data frame
      {
         // cout << "\n*** BRANCHING FOR DATA FRAME ***\n";
         sfile << ", class = 'data.frame')";
      }
      else  // write ending for matrix
      {
         // cout << "\n*** BRANCHING FOR MATRIX ***\n";
         sfile << "))";
      }
      if(iflast==0) sfile << ",";  // add comma if NOT last item in surrounding structure
      sfile << endl;
      return;
   }
   //===========================================================================================
   void write_s_matrix(ofstream& sfile, const dmatrix& xx, const char* xname,
      const int& ra, const int& rz, const int& ca, const int& cz)
   //
   // C++ function for ADMB to write a matrix as part of an S list.  This
   // writes the matrix header, the matrix data, and the row names. After
   // this function is used, the column names must be written separately
   // to complete the matrix.  That is done because the column names may or may
   // not be the same as the column indices.  (Row names are assumed to be the
   // same as the row indices, generally years.)
   //
   // M. H. Prager, December 2002
   //
   // ----------Arguments----------
   // sfile    Object of type ofstream to hold output.
   // xx       The matrix to be written
   // xname    String that is written as name of matrix
   // ca, cz   Starting and ending column indexes
   // ra, rz   Starting and ending row indexes
   {
      int ir, ic;

      //  Write the matrix header, which includes its name:
      sfile << xname << "= structure(c(";

      // Write the matrix data
      for(ic=ca; ic<=cz; ic++)
      {
         for(ir=ra; ir<=rz; ir++)
         {
         sfile << xx(ir,ic);
         if (ic==cz && ir==rz)
            {sfile << ")";}
         else
            {sfile << ", ";}
         }
      sfile << endl;
      }

     // Write dimensions of the matrix
     sfile << ", .Dim = c(" << (rz-ra+1);
     sfile << "," << (cz-ca+1 ) << ")," << endl;

     // Write row names
     sfile << ".Dimnames = list(c(";
     for(ir=ra; ir<=rz; ir++)
     {
       sfile << '"' << ir << '"';
       if(ir==rz)
          {sfile << ")," << endl;}
       else
          {sfile << ", ";}
     }
     return;
   }
   //===========================================================================================
   void write_s_imatrix(ofstream& sfile, const dmatrix& xx, const ivector &nn, const char* xname,
      const int& ra, const int& rz, const int& ca, const int& cz)
   //
   // C++ function for ADMB to write an indexed matrix as part of an S list.  This
   // writes the matrix header, the matrix data, and the row names. After
   // this function is used, the column names must be written separately
   // to complete the matrix.  That is done because the column names may or may
   // not be the same as the column indices.
   //
   // In constrast to the similar function write_s_matrix(), here the row names are
   // not assumed contiguous, but rather to be stored in an integer vector.
   //
   //
   // M. H. Prager, December 2002
   //
   // ----------Arguments----------
   // sfile    Object of type ofstream to hold output.
   // xx       The matrix to be written
   // nn       Integer vector with row (e.g. year) names
   // xname    String that is written as name of matrix
   // ca, cz   Starting and ending column indexes
   // ra, rz   Starting and ending row indexes
   {
      int ir, ic;

      //  Write the matrix header, which includes its name:
      sfile << xname << "= structure(c(";

      // Write the matrix data
      for(ic=ca; ic<=cz; ic++)         // columns (e.g., age classes)
      {
         for(ir=ra; ir<=rz; ir++)      // rows (e.g., years)
         {
         sfile << xx(ir,ic);
         if (ic==cz && ir==rz)
            {sfile << ")";}
         else
            {sfile << ", ";}
         }
      sfile << endl;
      }

     // Write dimensions of the matrix
     sfile << ", .Dim = c(" << (rz-ra+1);
     sfile << "," << (cz-ca+1 ) << ")," << endl;

     // Write row names

     sfile << ".Dimnames = list(c(";
     for(ir=ra; ir<=rz; ir++)
     {
       sfile << '"' << nn(ir) << '"';
       if(ir==rz)
          {sfile << ")," << endl;}
       else
          {sfile << ", ";}
     }
     return;
   }
   //===========================================================================================

