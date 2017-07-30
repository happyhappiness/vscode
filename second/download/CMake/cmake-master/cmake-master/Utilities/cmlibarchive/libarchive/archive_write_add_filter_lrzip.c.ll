; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_lrzip.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.write_lrzip = type { %struct.archive_write_program_data*, i32, i32 }
%struct.archive_write_program_data = type opaque

@.str = private unnamed_addr constant [31 x i8] c"archive_write_add_filter_lrzip\00", align 1
@.str.1 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"lrzip\00", align 1
@.str.3 = private unnamed_addr constant [51 x i8] c"Using external lrzip program for lrzip compression\00", align 1
@.str.4 = private unnamed_addr constant [12 x i8] c"compression\00", align 1
@.str.5 = private unnamed_addr constant [6 x i8] c"bzip2\00", align 1
@.str.6 = private unnamed_addr constant [5 x i8] c"gzip\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c"lzo\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.9 = private unnamed_addr constant [5 x i8] c"zpaq\00", align 1
@.str.10 = private unnamed_addr constant [18 x i8] c"compression-level\00", align 1
@.str.11 = private unnamed_addr constant [9 x i8] c"lrzip -q\00", align 1
@.str.12 = private unnamed_addr constant [4 x i8] c" -b\00", align 1
@.str.13 = private unnamed_addr constant [4 x i8] c" -g\00", align 1
@.str.14 = private unnamed_addr constant [4 x i8] c" -l\00", align 1
@.str.15 = private unnamed_addr constant [4 x i8] c" -n\00", align 1
@.str.16 = private unnamed_addr constant [4 x i8] c" -z\00", align 1
@.str.17 = private unnamed_addr constant [5 x i8] c" -L \00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_lrzip(%struct.archive* %_a) #0 !dbg !24 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_lrzip*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !159, metadata !160), !dbg !161
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !162, metadata !160), !dbg !163
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !164
  %call = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %0), !dbg !165
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !163
  call void @llvm.dbg.declare(metadata %struct.write_lrzip** %data, metadata !166, metadata !160), !dbg !167
  br label %do.body, !dbg !168

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !169, metadata !160), !dbg !171
  %1 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !172
  %call1 = call i32 @__archive_check_magic(%struct.archive* %1, i32 -1329217314, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0)), !dbg !172
  store i32 %call1, i32* %magic_test, align 4, !dbg !172
  %2 = load i32, i32* %magic_test, align 4, !dbg !172
  %cmp = icmp eq i32 %2, -30, !dbg !172
  br i1 %cmp, label %if.then, label %if.end, !dbg !172

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !174
  br label %return, !dbg !174

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !177

do.end:                                           ; preds = %if.end
  %call2 = call noalias i8* @calloc(i64 1, i64 16) #5, !dbg !179
  %3 = bitcast i8* %call2 to %struct.write_lrzip*, !dbg !179
  store %struct.write_lrzip* %3, %struct.write_lrzip** %data, align 8, !dbg !180
  %4 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !181
  %cmp3 = icmp eq %struct.write_lrzip* %4, null, !dbg !183
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !184

if.then4:                                         ; preds = %do.end
  %5 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !185
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %5, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i32 0, i32 0)), !dbg !187
  store i32 -30, i32* %retval, align 4, !dbg !188
  br label %return, !dbg !188

if.end5:                                          ; preds = %do.end
  %call6 = call %struct.archive_write_program_data* @__archive_write_program_allocate(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0)), !dbg !189
  %6 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !190
  %pdata = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %6, i32 0, i32 0, !dbg !191
  store %struct.archive_write_program_data* %call6, %struct.archive_write_program_data** %pdata, align 8, !dbg !192
  %7 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !193
  %pdata7 = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %7, i32 0, i32 0, !dbg !195
  %8 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata7, align 8, !dbg !195
  %cmp8 = icmp eq %struct.archive_write_program_data* %8, null, !dbg !196
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !197

if.then9:                                         ; preds = %if.end5
  %9 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !198
  %10 = bitcast %struct.write_lrzip* %9 to i8*, !dbg !198
  call void @free(i8* %10) #5, !dbg !200
  %11 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !201
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %11, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i32 0, i32 0)), !dbg !202
  store i32 -30, i32* %retval, align 4, !dbg !203
  br label %return, !dbg !203

if.end10:                                         ; preds = %if.end5
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !204
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 9, !dbg !205
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i8** %name, align 8, !dbg !206
  %13 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !207
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %13, i32 0, i32 10, !dbg !208
  store i32 10, i32* %code, align 8, !dbg !209
  %14 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !210
  %15 = bitcast %struct.write_lrzip* %14 to i8*, !dbg !210
  %16 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !211
  %data11 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %16, i32 0, i32 8, !dbg !212
  store i8* %15, i8** %data11, align 8, !dbg !213
  %17 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !214
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %17, i32 0, i32 4, !dbg !215
  store i32 (%struct.archive_write_filter*)* @archive_write_lrzip_open, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !216
  %18 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !217
  %options = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %18, i32 0, i32 3, !dbg !218
  store i32 (%struct.archive_write_filter*, i8*, i8*)* @archive_write_lrzip_options, i32 (%struct.archive_write_filter*, i8*, i8*)** %options, align 8, !dbg !219
  %19 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !220
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %19, i32 0, i32 5, !dbg !221
  store i32 (%struct.archive_write_filter*, i8*, i64)* @archive_write_lrzip_write, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !222
  %20 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !223
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %20, i32 0, i32 6, !dbg !224
  store i32 (%struct.archive_write_filter*)* @archive_write_lrzip_close, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !225
  %21 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !226
  %free = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %21, i32 0, i32 7, !dbg !227
  store i32 (%struct.archive_write_filter*)* @archive_write_lrzip_free, i32 (%struct.archive_write_filter*)** %free, align 8, !dbg !228
  %22 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !229
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %22, i32 -1, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.3, i32 0, i32 0)), !dbg !230
  store i32 -20, i32* %retval, align 4, !dbg !231
  br label %return, !dbg !231

return:                                           ; preds = %if.end10, %if.then9, %if.then4, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !232
  ret i32 %23, !dbg !232
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive*) #2

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare %struct.archive_write_program_data* @__archive_write_program_allocate(i8*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lrzip_open(%struct.archive_write_filter* %f) #0 !dbg !152 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_lrzip*, align 8
  %as = alloca %struct.archive_string, align 8
  %r = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !233, metadata !160), !dbg !234
  call void @llvm.dbg.declare(metadata %struct.write_lrzip** %data, metadata !235, metadata !160), !dbg !236
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !237
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !238
  %1 = load i8*, i8** %data1, align 8, !dbg !238
  %2 = bitcast i8* %1 to %struct.write_lrzip*, !dbg !239
  store %struct.write_lrzip* %2, %struct.write_lrzip** %data, align 8, !dbg !236
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !240, metadata !160), !dbg !241
  call void @llvm.dbg.declare(metadata i32* %r, metadata !242, metadata !160), !dbg !243
  br label %do.body, !dbg !244

do.body:                                          ; preds = %entry
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !245
  store i8* null, i8** %s, align 8, !dbg !245
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !245
  store i64 0, i64* %length, align 8, !dbg !245
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !245
  store i64 0, i64* %buffer_length, align 8, !dbg !245
  br label %do.end, !dbg !245

do.end:                                           ; preds = %do.body
  %length2 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !248
  store i64 0, i64* %length2, align 8, !dbg !248
  %call = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.11, i32 0, i32 0), i64 8), !dbg !248
  %3 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !249
  %compression = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %3, i32 0, i32 2, !dbg !250
  %4 = load i32, i32* %compression, align 4, !dbg !250
  switch i32 %4, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb3
    i32 2, label %sw.bb5
    i32 3, label %sw.bb7
    i32 4, label %sw.bb9
    i32 5, label %sw.bb11
  ], !dbg !251

sw.bb:                                            ; preds = %do.end
  br label %sw.epilog, !dbg !252

sw.bb3:                                           ; preds = %do.end
  %call4 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.12, i32 0, i32 0)), !dbg !254
  br label %sw.epilog, !dbg !255

sw.bb5:                                           ; preds = %do.end
  %call6 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.13, i32 0, i32 0)), !dbg !256
  br label %sw.epilog, !dbg !257

sw.bb7:                                           ; preds = %do.end
  %call8 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.14, i32 0, i32 0)), !dbg !258
  br label %sw.epilog, !dbg !259

sw.bb9:                                           ; preds = %do.end
  %call10 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.15, i32 0, i32 0)), !dbg !260
  br label %sw.epilog, !dbg !261

sw.bb11:                                          ; preds = %do.end
  %call12 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.16, i32 0, i32 0)), !dbg !262
  br label %sw.epilog, !dbg !263

sw.epilog:                                        ; preds = %do.end, %sw.bb11, %sw.bb9, %sw.bb7, %sw.bb5, %sw.bb3, %sw.bb
  %5 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !264
  %compression_level = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %5, i32 0, i32 1, !dbg !266
  %6 = load i32, i32* %compression_level, align 8, !dbg !266
  %cmp = icmp sgt i32 %6, 0, !dbg !267
  br i1 %cmp, label %if.then, label %if.end, !dbg !268

if.then:                                          ; preds = %sw.epilog
  %call13 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0)), !dbg !269
  %7 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !271
  %compression_level14 = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %7, i32 0, i32 1, !dbg !272
  %8 = load i32, i32* %compression_level14, align 8, !dbg !272
  %add = add nsw i32 48, %8, !dbg !273
  %conv = trunc i32 %add to i8, !dbg !274
  %call15 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext %conv), !dbg !275
  br label %if.end, !dbg !276

if.end:                                           ; preds = %if.then, %sw.epilog
  %9 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !277
  %10 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !278
  %pdata = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %10, i32 0, i32 0, !dbg !279
  %11 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !279
  %s16 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !280
  %12 = load i8*, i8** %s16, align 8, !dbg !280
  %call17 = call i32 @__archive_write_program_open(%struct.archive_write_filter* %9, %struct.archive_write_program_data* %11, i8* %12), !dbg !281
  store i32 %call17, i32* %r, align 4, !dbg !282
  call void @archive_string_free(%struct.archive_string* %as), !dbg !283
  %13 = load i32, i32* %r, align 4, !dbg !284
  ret i32 %13, !dbg !285
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lrzip_options(%struct.archive_write_filter* %f, i8* %key, i8* %value) #0 !dbg !126 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %data = alloca %struct.write_lrzip*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !286, metadata !160), !dbg !287
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !288, metadata !160), !dbg !289
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !290, metadata !160), !dbg !291
  call void @llvm.dbg.declare(metadata %struct.write_lrzip** %data, metadata !292, metadata !160), !dbg !293
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !294
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !295
  %1 = load i8*, i8** %data1, align 8, !dbg !295
  %2 = bitcast i8* %1 to %struct.write_lrzip*, !dbg !296
  store %struct.write_lrzip* %2, %struct.write_lrzip** %data, align 8, !dbg !293
  %3 = load i8*, i8** %key.addr, align 8, !dbg !297
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.4, i32 0, i32 0)) #6, !dbg !299
  %cmp = icmp eq i32 %call, 0, !dbg !300
  br i1 %cmp, label %if.then, label %if.else33, !dbg !301

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %value.addr, align 8, !dbg !302
  %cmp2 = icmp eq i8* %4, null, !dbg !305
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !306

if.then3:                                         ; preds = %if.then
  store i32 -20, i32* %retval, align 4, !dbg !307
  br label %return, !dbg !307

if.else:                                          ; preds = %if.then
  %5 = load i8*, i8** %value.addr, align 8, !dbg !308
  %call4 = call i32 @strcmp(i8* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.5, i32 0, i32 0)) #6, !dbg !310
  %cmp5 = icmp eq i32 %call4, 0, !dbg !311
  br i1 %cmp5, label %if.then6, label %if.else7, !dbg !312

if.then6:                                         ; preds = %if.else
  %6 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !313
  %compression = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %6, i32 0, i32 2, !dbg !314
  store i32 1, i32* %compression, align 4, !dbg !315
  br label %if.end31, !dbg !313

if.else7:                                         ; preds = %if.else
  %7 = load i8*, i8** %value.addr, align 8, !dbg !316
  %call8 = call i32 @strcmp(i8* %7, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i32 0, i32 0)) #6, !dbg !318
  %cmp9 = icmp eq i32 %call8, 0, !dbg !319
  br i1 %cmp9, label %if.then10, label %if.else12, !dbg !320

if.then10:                                        ; preds = %if.else7
  %8 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !321
  %compression11 = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %8, i32 0, i32 2, !dbg !322
  store i32 2, i32* %compression11, align 4, !dbg !323
  br label %if.end30, !dbg !321

if.else12:                                        ; preds = %if.else7
  %9 = load i8*, i8** %value.addr, align 8, !dbg !324
  %call13 = call i32 @strcmp(i8* %9, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0)) #6, !dbg !326
  %cmp14 = icmp eq i32 %call13, 0, !dbg !327
  br i1 %cmp14, label %if.then15, label %if.else17, !dbg !328

if.then15:                                        ; preds = %if.else12
  %10 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !329
  %compression16 = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %10, i32 0, i32 2, !dbg !330
  store i32 3, i32* %compression16, align 4, !dbg !331
  br label %if.end29, !dbg !329

if.else17:                                        ; preds = %if.else12
  %11 = load i8*, i8** %value.addr, align 8, !dbg !332
  %call18 = call i32 @strcmp(i8* %11, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i32 0, i32 0)) #6, !dbg !334
  %cmp19 = icmp eq i32 %call18, 0, !dbg !335
  br i1 %cmp19, label %if.then20, label %if.else22, !dbg !336

if.then20:                                        ; preds = %if.else17
  %12 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !337
  %compression21 = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %12, i32 0, i32 2, !dbg !338
  store i32 4, i32* %compression21, align 4, !dbg !339
  br label %if.end28, !dbg !337

if.else22:                                        ; preds = %if.else17
  %13 = load i8*, i8** %value.addr, align 8, !dbg !340
  %call23 = call i32 @strcmp(i8* %13, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.9, i32 0, i32 0)) #6, !dbg !342
  %cmp24 = icmp eq i32 %call23, 0, !dbg !343
  br i1 %cmp24, label %if.then25, label %if.else27, !dbg !344

if.then25:                                        ; preds = %if.else22
  %14 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !345
  %compression26 = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %14, i32 0, i32 2, !dbg !346
  store i32 5, i32* %compression26, align 4, !dbg !347
  br label %if.end, !dbg !345

if.else27:                                        ; preds = %if.else22
  store i32 -20, i32* %retval, align 4, !dbg !348
  br label %return, !dbg !348

if.end:                                           ; preds = %if.then25
  br label %if.end28

if.end28:                                         ; preds = %if.end, %if.then20
  br label %if.end29

if.end29:                                         ; preds = %if.end28, %if.then15
  br label %if.end30

if.end30:                                         ; preds = %if.end29, %if.then10
  br label %if.end31

if.end31:                                         ; preds = %if.end30, %if.then6
  br label %if.end32

if.end32:                                         ; preds = %if.end31
  store i32 0, i32* %retval, align 4, !dbg !349
  br label %return, !dbg !349

if.else33:                                        ; preds = %entry
  %15 = load i8*, i8** %key.addr, align 8, !dbg !350
  %call34 = call i32 @strcmp(i8* %15, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.10, i32 0, i32 0)) #6, !dbg !352
  %cmp35 = icmp eq i32 %call34, 0, !dbg !353
  br i1 %cmp35, label %if.then36, label %if.end53, !dbg !354

if.then36:                                        ; preds = %if.else33
  %16 = load i8*, i8** %value.addr, align 8, !dbg !355
  %cmp37 = icmp eq i8* %16, null, !dbg !358
  br i1 %cmp37, label %if.then49, label %lor.lhs.false, !dbg !359

lor.lhs.false:                                    ; preds = %if.then36
  %17 = load i8*, i8** %value.addr, align 8, !dbg !360
  %arrayidx = getelementptr inbounds i8, i8* %17, i64 0, !dbg !360
  %18 = load i8, i8* %arrayidx, align 1, !dbg !360
  %conv = sext i8 %18 to i32, !dbg !360
  %cmp38 = icmp sge i32 %conv, 49, !dbg !362
  br i1 %cmp38, label %land.lhs.true, label %if.then49, !dbg !363

land.lhs.true:                                    ; preds = %lor.lhs.false
  %19 = load i8*, i8** %value.addr, align 8, !dbg !364
  %arrayidx40 = getelementptr inbounds i8, i8* %19, i64 0, !dbg !364
  %20 = load i8, i8* %arrayidx40, align 1, !dbg !364
  %conv41 = sext i8 %20 to i32, !dbg !364
  %cmp42 = icmp sle i32 %conv41, 57, !dbg !366
  br i1 %cmp42, label %lor.lhs.false44, label %if.then49, !dbg !367

lor.lhs.false44:                                  ; preds = %land.lhs.true
  %21 = load i8*, i8** %value.addr, align 8, !dbg !368
  %arrayidx45 = getelementptr inbounds i8, i8* %21, i64 1, !dbg !368
  %22 = load i8, i8* %arrayidx45, align 1, !dbg !368
  %conv46 = sext i8 %22 to i32, !dbg !368
  %cmp47 = icmp ne i32 %conv46, 0, !dbg !369
  br i1 %cmp47, label %if.then49, label %if.end50, !dbg !370

if.then49:                                        ; preds = %lor.lhs.false44, %land.lhs.true, %lor.lhs.false, %if.then36
  store i32 -20, i32* %retval, align 4, !dbg !372
  br label %return, !dbg !372

if.end50:                                         ; preds = %lor.lhs.false44
  %23 = load i8*, i8** %value.addr, align 8, !dbg !373
  %arrayidx51 = getelementptr inbounds i8, i8* %23, i64 0, !dbg !373
  %24 = load i8, i8* %arrayidx51, align 1, !dbg !373
  %conv52 = sext i8 %24 to i32, !dbg !373
  %sub = sub nsw i32 %conv52, 48, !dbg !374
  %25 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !375
  %compression_level = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %25, i32 0, i32 1, !dbg !376
  store i32 %sub, i32* %compression_level, align 8, !dbg !377
  store i32 0, i32* %retval, align 4, !dbg !378
  br label %return, !dbg !378

if.end53:                                         ; preds = %if.else33
  br label %if.end54

if.end54:                                         ; preds = %if.end53
  store i32 -20, i32* %retval, align 4, !dbg !379
  br label %return, !dbg !379

return:                                           ; preds = %if.end54, %if.end50, %if.then49, %if.end32, %if.else27, %if.then3
  %26 = load i32, i32* %retval, align 4, !dbg !380
  ret i32 %26, !dbg !380
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lrzip_write(%struct.archive_write_filter* %f, i8* %buff, i64 %length) #0 !dbg !153 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %data = alloca %struct.write_lrzip*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !381, metadata !160), !dbg !382
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !383, metadata !160), !dbg !384
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !385, metadata !160), !dbg !386
  call void @llvm.dbg.declare(metadata %struct.write_lrzip** %data, metadata !387, metadata !160), !dbg !388
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !389
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !390
  %1 = load i8*, i8** %data1, align 8, !dbg !390
  %2 = bitcast i8* %1 to %struct.write_lrzip*, !dbg !391
  store %struct.write_lrzip* %2, %struct.write_lrzip** %data, align 8, !dbg !388
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !392
  %4 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !393
  %pdata = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %4, i32 0, i32 0, !dbg !394
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !394
  %6 = load i8*, i8** %buff.addr, align 8, !dbg !395
  %7 = load i64, i64* %length.addr, align 8, !dbg !396
  %call = call i32 @__archive_write_program_write(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5, i8* %6, i64 %7), !dbg !397
  ret i32 %call, !dbg !398
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lrzip_close(%struct.archive_write_filter* %f) #0 !dbg !154 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_lrzip*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !399, metadata !160), !dbg !400
  call void @llvm.dbg.declare(metadata %struct.write_lrzip** %data, metadata !401, metadata !160), !dbg !402
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !403
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !404
  %1 = load i8*, i8** %data1, align 8, !dbg !404
  %2 = bitcast i8* %1 to %struct.write_lrzip*, !dbg !405
  store %struct.write_lrzip* %2, %struct.write_lrzip** %data, align 8, !dbg !402
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !406
  %4 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !407
  %pdata = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %4, i32 0, i32 0, !dbg !408
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !408
  %call = call i32 @__archive_write_program_close(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5), !dbg !409
  ret i32 %call, !dbg !410
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lrzip_free(%struct.archive_write_filter* %f) #0 !dbg !155 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_lrzip*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !411, metadata !160), !dbg !412
  call void @llvm.dbg.declare(metadata %struct.write_lrzip** %data, metadata !413, metadata !160), !dbg !414
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !415
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !416
  %1 = load i8*, i8** %data1, align 8, !dbg !416
  %2 = bitcast i8* %1 to %struct.write_lrzip*, !dbg !417
  store %struct.write_lrzip* %2, %struct.write_lrzip** %data, align 8, !dbg !414
  %3 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !418
  %pdata = getelementptr inbounds %struct.write_lrzip, %struct.write_lrzip* %3, i32 0, i32 0, !dbg !419
  %4 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !419
  %call = call i32 @__archive_write_program_free(%struct.archive_write_program_data* %4), !dbg !420
  %5 = load %struct.write_lrzip*, %struct.write_lrzip** %data, align 8, !dbg !421
  %6 = bitcast %struct.write_lrzip* %5 to i8*, !dbg !421
  call void @free(i8* %6) #5, !dbg !422
  ret i32 0, !dbg !423
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare %struct.archive_string* @archive_strcat(%struct.archive_string*, i8*) #2

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

declare i32 @__archive_write_program_open(%struct.archive_write_filter*, %struct.archive_write_program_data*, i8*) #2

declare void @archive_string_free(%struct.archive_string*) #2

declare i32 @__archive_write_program_write(%struct.archive_write_filter*, %struct.archive_write_program_data*, i8*, i64) #2

declare i32 @__archive_write_program_close(%struct.archive_write_filter*, %struct.archive_write_program_data*) #2

declare i32 @__archive_write_program_free(%struct.archive_write_program_data*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!156, !157}
!llvm.ident = !{!158}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !20, subprograms: !23)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_lrzip.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !4, file: !1, line: 47, size: 32, align: 32, elements: !13)
!4 = !DICompositeType(tag: DW_TAG_structure_type, name: "write_lrzip", file: !1, line: 44, size: 128, align: 64, elements: !5)
!5 = !{!6, !10, !12}
!6 = !DIDerivedType(tag: DW_TAG_member, name: "pdata", scope: !4, file: !1, line: 45, baseType: !7, size: 64, align: 64)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_program_data", file: !9, line: 146, flags: DIFlagFwdDecl)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!10 = !DIDerivedType(tag: DW_TAG_member, name: "compression_level", scope: !4, file: !1, line: 46, baseType: !11, size: 32, align: 32, offset: 64)
!11 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!12 = !DIDerivedType(tag: DW_TAG_member, name: "compression", scope: !4, file: !1, line: 47, baseType: !3, size: 32, align: 32, offset: 96)
!13 = !{!14, !15, !16, !17, !18, !19}
!14 = !DIEnumerator(name: "lzma", value: 0)
!15 = !DIEnumerator(name: "bzip2", value: 1)
!16 = !DIEnumerator(name: "gzip", value: 2)
!17 = !DIEnumerator(name: "lzo", value: 3)
!18 = !DIEnumerator(name: "none", value: 4)
!19 = !DIEnumerator(name: "zpaq", value: 5)
!20 = !{!21, !22}
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64, align: 64)
!23 = !{!24, !126, !152, !153, !154, !155}
!24 = distinct !DISubprogram(name: "archive_write_add_filter_lrzip", scope: !1, file: !1, line: 59, type: !25, isLocal: false, isDefinition: true, scopeLine: 60, flags: DIFlagPrototyped, isOptimized: false, variables: !125)
!25 = !DISubroutineType(types: !26)
!26 = !{!11, !27}
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !29, line: 89, size: 1280, align: 64, elements: !30)
!29 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!30 = !{!31, !33, !34, !98, !99, !100, !101, !102, !103, !104, !105, !113, !114, !115, !116, !119, !120, !121, !122, !123, !124}
!31 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !28, file: !29, line: 96, baseType: !32, size: 32, align: 32)
!32 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !28, file: !29, line: 97, baseType: !32, size: 32, align: 32, offset: 32)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !28, file: !29, line: 103, baseType: !35, size: 64, align: 64, offset: 64)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !29, line: 63, size: 832, align: 64, elements: !37)
!37 = !{!38, !40, !41, !48, !49, !63, !69, !74, !75, !82, !83, !87, !91}
!38 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !36, file: !29, line: 64, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !36, file: !29, line: 65, baseType: !39, size: 64, align: 64, offset: 64)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !36, file: !29, line: 66, baseType: !42, size: 64, align: 64, offset: 128)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DISubroutineType(types: !44)
!44 = !{!11, !27, !45}
!45 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !46, size: 64, align: 64)
!46 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !47, line: 180, flags: DIFlagFwdDecl)
!47 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !36, file: !29, line: 68, baseType: !39, size: 64, align: 64, offset: 192)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !36, file: !29, line: 69, baseType: !50, size: 64, align: 64, offset: 256)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DISubroutineType(types: !52)
!52 = !{!53, !27, !58, !60}
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !54, line: 109, baseType: !55)
!54 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !56, line: 172, baseType: !57)
!56 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!57 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!60 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !61, line: 62, baseType: !62)
!61 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!62 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !36, file: !29, line: 71, baseType: !64, size: 64, align: 64, offset: 320)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!65 = !DISubroutineType(types: !66)
!66 = !{!53, !27, !58, !60, !67}
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !68, line: 40, baseType: !57)
!68 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!69 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !36, file: !29, line: 74, baseType: !70, size: 64, align: 64, offset: 384)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !71, size: 64, align: 64)
!71 = !DISubroutineType(types: !72)
!72 = !{!11, !27, !73}
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !36, file: !29, line: 76, baseType: !42, size: 64, align: 64, offset: 448)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !36, file: !29, line: 78, baseType: !76, size: 64, align: 64, offset: 512)
!76 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !77, size: 64, align: 64)
!77 = !DISubroutineType(types: !78)
!78 = !{!11, !27, !79, !80, !81}
!79 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !36, file: !29, line: 81, baseType: !39, size: 64, align: 64, offset: 576)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !36, file: !29, line: 82, baseType: !84, size: 64, align: 64, offset: 640)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!85 = !DISubroutineType(types: !86)
!86 = !{!67, !27, !11}
!87 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !36, file: !29, line: 83, baseType: !88, size: 64, align: 64, offset: 704)
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!89 = !DISubroutineType(types: !90)
!90 = !{!11, !27, !11}
!91 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !36, file: !29, line: 84, baseType: !92, size: 64, align: 64, offset: 768)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DISubroutineType(types: !94)
!94 = !{!95, !27, !11}
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !97)
!97 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !28, file: !29, line: 105, baseType: !11, size: 32, align: 32, offset: 128)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !28, file: !29, line: 106, baseType: !95, size: 64, align: 64, offset: 192)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !28, file: !29, line: 108, baseType: !11, size: 32, align: 32, offset: 256)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !28, file: !29, line: 109, baseType: !95, size: 64, align: 64, offset: 320)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !28, file: !29, line: 112, baseType: !11, size: 32, align: 32, offset: 384)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !28, file: !29, line: 114, baseType: !11, size: 32, align: 32, offset: 416)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !28, file: !29, line: 115, baseType: !95, size: 64, align: 64, offset: 448)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !28, file: !29, line: 116, baseType: !106, size: 192, align: 64, offset: 512)
!106 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !107, line: 58, size: 192, align: 64, elements: !108)
!107 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!108 = !{!109, !111, !112}
!109 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !106, file: !107, line: 59, baseType: !110, size: 64, align: 64)
!110 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !106, file: !107, line: 60, baseType: !60, size: 64, align: 64, offset: 64)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !106, file: !107, line: 61, baseType: !60, size: 64, align: 64, offset: 128)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !28, file: !29, line: 118, baseType: !110, size: 64, align: 64, offset: 704)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !28, file: !29, line: 119, baseType: !32, size: 32, align: 32, offset: 768)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !28, file: !29, line: 120, baseType: !32, size: 32, align: 32, offset: 800)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !28, file: !29, line: 121, baseType: !117, size: 64, align: 64, offset: 832)
!117 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !118, size: 64, align: 64)
!118 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !107, line: 70, flags: DIFlagFwdDecl)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !28, file: !29, line: 127, baseType: !95, size: 64, align: 64, offset: 896)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !28, file: !29, line: 128, baseType: !67, size: 64, align: 64, offset: 960)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !28, file: !29, line: 129, baseType: !67, size: 64, align: 64, offset: 1024)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !28, file: !29, line: 130, baseType: !60, size: 64, align: 64, offset: 1088)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !28, file: !29, line: 137, baseType: !97, size: 8, align: 8, offset: 1152)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !28, file: !29, line: 138, baseType: !60, size: 64, align: 64, offset: 1216)
!125 = !{}
!126 = distinct !DISubprogram(name: "archive_write_lrzip_options", scope: !1, file: !1, line: 96, type: !127, isLocal: true, isDefinition: true, scopeLine: 98, flags: DIFlagPrototyped, isOptimized: false, variables: !125)
!127 = !DISubroutineType(types: !128)
!128 = !{!11, !129, !95, !95}
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !9, line: 43, size: 768, align: 64, elements: !131)
!131 = !{!132, !133, !134, !135, !137, !141, !145, !146, !147, !148, !149, !150, !151}
!132 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !130, file: !9, line: 44, baseType: !67, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !130, file: !9, line: 45, baseType: !27, size: 64, align: 64, offset: 64)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !130, file: !9, line: 46, baseType: !129, size: 64, align: 64, offset: 128)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !130, file: !9, line: 47, baseType: !136, size: 64, align: 64, offset: 192)
!136 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !130, file: !9, line: 49, baseType: !138, size: 64, align: 64, offset: 256)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DISubroutineType(types: !140)
!140 = !{!11, !129}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !130, file: !9, line: 50, baseType: !142, size: 64, align: 64, offset: 320)
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !143, size: 64, align: 64)
!143 = !DISubroutineType(types: !144)
!144 = !{!11, !129, !58, !60}
!145 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !130, file: !9, line: 51, baseType: !138, size: 64, align: 64, offset: 384)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !130, file: !9, line: 52, baseType: !138, size: 64, align: 64, offset: 448)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !130, file: !9, line: 53, baseType: !21, size: 64, align: 64, offset: 512)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !130, file: !9, line: 54, baseType: !95, size: 64, align: 64, offset: 576)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !130, file: !9, line: 55, baseType: !11, size: 32, align: 32, offset: 640)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !130, file: !9, line: 56, baseType: !11, size: 32, align: 32, offset: 672)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !130, file: !9, line: 57, baseType: !11, size: 32, align: 32, offset: 704)
!152 = distinct !DISubprogram(name: "archive_write_lrzip_open", scope: !1, file: !1, line: 131, type: !139, isLocal: true, isDefinition: true, scopeLine: 132, flags: DIFlagPrototyped, isOptimized: false, variables: !125)
!153 = distinct !DISubprogram(name: "archive_write_lrzip_write", scope: !1, file: !1, line: 173, type: !143, isLocal: true, isDefinition: true, scopeLine: 175, flags: DIFlagPrototyped, isOptimized: false, variables: !125)
!154 = distinct !DISubprogram(name: "archive_write_lrzip_close", scope: !1, file: !1, line: 182, type: !139, isLocal: true, isDefinition: true, scopeLine: 183, flags: DIFlagPrototyped, isOptimized: false, variables: !125)
!155 = distinct !DISubprogram(name: "archive_write_lrzip_free", scope: !1, file: !1, line: 190, type: !139, isLocal: true, isDefinition: true, scopeLine: 191, flags: DIFlagPrototyped, isOptimized: false, variables: !125)
!156 = !{i32 2, !"Dwarf Version", i32 4}
!157 = !{i32 2, !"Debug Info Version", i32 3}
!158 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!159 = !DILocalVariable(name: "_a", arg: 1, scope: !24, file: !1, line: 59, type: !27)
!160 = !DIExpression()
!161 = !DILocation(line: 59, column: 48, scope: !24)
!162 = !DILocalVariable(name: "f", scope: !24, file: !1, line: 61, type: !129)
!163 = !DILocation(line: 61, column: 31, scope: !24)
!164 = !DILocation(line: 61, column: 67, scope: !24)
!165 = !DILocation(line: 61, column: 35, scope: !24)
!166 = !DILocalVariable(name: "data", scope: !24, file: !1, line: 62, type: !22)
!167 = !DILocation(line: 62, column: 22, scope: !24)
!168 = !DILocation(line: 64, column: 2, scope: !24)
!169 = !DILocalVariable(name: "magic_test", scope: !170, file: !1, line: 64, type: !11)
!170 = distinct !DILexicalBlock(scope: !24, file: !1, line: 64, column: 2)
!171 = !DILocation(line: 64, column: 2, scope: !170)
!172 = !DILocation(line: 64, column: 2, scope: !173)
!173 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 1)
!174 = !DILocation(line: 64, column: 2, scope: !175)
!175 = !DILexicalBlockFile(scope: !176, file: !1, discriminator: 2)
!176 = distinct !DILexicalBlock(scope: !170, file: !1, line: 64, column: 2)
!177 = !DILocation(line: 64, column: 2, scope: !178)
!178 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 3)
!179 = !DILocation(line: 67, column: 9, scope: !24)
!180 = !DILocation(line: 67, column: 7, scope: !24)
!181 = !DILocation(line: 68, column: 6, scope: !182)
!182 = distinct !DILexicalBlock(scope: !24, file: !1, line: 68, column: 6)
!183 = !DILocation(line: 68, column: 11, scope: !182)
!184 = !DILocation(line: 68, column: 6, scope: !24)
!185 = !DILocation(line: 69, column: 21, scope: !186)
!186 = distinct !DILexicalBlock(scope: !182, file: !1, line: 68, column: 20)
!187 = !DILocation(line: 69, column: 3, scope: !186)
!188 = !DILocation(line: 70, column: 3, scope: !186)
!189 = !DILocation(line: 72, column: 16, scope: !24)
!190 = !DILocation(line: 72, column: 2, scope: !24)
!191 = !DILocation(line: 72, column: 8, scope: !24)
!192 = !DILocation(line: 72, column: 14, scope: !24)
!193 = !DILocation(line: 73, column: 6, scope: !194)
!194 = distinct !DILexicalBlock(scope: !24, file: !1, line: 73, column: 6)
!195 = !DILocation(line: 73, column: 12, scope: !194)
!196 = !DILocation(line: 73, column: 18, scope: !194)
!197 = !DILocation(line: 73, column: 6, scope: !24)
!198 = !DILocation(line: 74, column: 8, scope: !199)
!199 = distinct !DILexicalBlock(scope: !194, file: !1, line: 73, column: 27)
!200 = !DILocation(line: 74, column: 3, scope: !199)
!201 = !DILocation(line: 75, column: 21, scope: !199)
!202 = !DILocation(line: 75, column: 3, scope: !199)
!203 = !DILocation(line: 76, column: 3, scope: !199)
!204 = !DILocation(line: 79, column: 2, scope: !24)
!205 = !DILocation(line: 79, column: 5, scope: !24)
!206 = !DILocation(line: 79, column: 10, scope: !24)
!207 = !DILocation(line: 80, column: 2, scope: !24)
!208 = !DILocation(line: 80, column: 5, scope: !24)
!209 = !DILocation(line: 80, column: 10, scope: !24)
!210 = !DILocation(line: 81, column: 12, scope: !24)
!211 = !DILocation(line: 81, column: 2, scope: !24)
!212 = !DILocation(line: 81, column: 5, scope: !24)
!213 = !DILocation(line: 81, column: 10, scope: !24)
!214 = !DILocation(line: 82, column: 2, scope: !24)
!215 = !DILocation(line: 82, column: 5, scope: !24)
!216 = !DILocation(line: 82, column: 10, scope: !24)
!217 = !DILocation(line: 83, column: 2, scope: !24)
!218 = !DILocation(line: 83, column: 5, scope: !24)
!219 = !DILocation(line: 83, column: 13, scope: !24)
!220 = !DILocation(line: 84, column: 2, scope: !24)
!221 = !DILocation(line: 84, column: 5, scope: !24)
!222 = !DILocation(line: 84, column: 11, scope: !24)
!223 = !DILocation(line: 85, column: 2, scope: !24)
!224 = !DILocation(line: 85, column: 5, scope: !24)
!225 = !DILocation(line: 85, column: 11, scope: !24)
!226 = !DILocation(line: 86, column: 2, scope: !24)
!227 = !DILocation(line: 86, column: 5, scope: !24)
!228 = !DILocation(line: 86, column: 10, scope: !24)
!229 = !DILocation(line: 90, column: 20, scope: !24)
!230 = !DILocation(line: 90, column: 2, scope: !24)
!231 = !DILocation(line: 92, column: 2, scope: !24)
!232 = !DILocation(line: 93, column: 1, scope: !24)
!233 = !DILocalVariable(name: "f", arg: 1, scope: !152, file: !1, line: 131, type: !129)
!234 = !DILocation(line: 131, column: 55, scope: !152)
!235 = !DILocalVariable(name: "data", scope: !152, file: !1, line: 133, type: !22)
!236 = !DILocation(line: 133, column: 22, scope: !152)
!237 = !DILocation(line: 133, column: 51, scope: !152)
!238 = !DILocation(line: 133, column: 54, scope: !152)
!239 = !DILocation(line: 133, column: 29, scope: !152)
!240 = !DILocalVariable(name: "as", scope: !152, file: !1, line: 134, type: !106)
!241 = !DILocation(line: 134, column: 24, scope: !152)
!242 = !DILocalVariable(name: "r", scope: !152, file: !1, line: 135, type: !11)
!243 = !DILocation(line: 135, column: 6, scope: !152)
!244 = !DILocation(line: 137, column: 2, scope: !152)
!245 = !DILocation(line: 137, column: 2, scope: !246)
!246 = !DILexicalBlockFile(scope: !247, file: !1, discriminator: 1)
!247 = distinct !DILexicalBlock(scope: !152, file: !1, line: 137, column: 2)
!248 = !DILocation(line: 138, column: 2, scope: !152)
!249 = !DILocation(line: 141, column: 10, scope: !152)
!250 = !DILocation(line: 141, column: 16, scope: !152)
!251 = !DILocation(line: 141, column: 2, scope: !152)
!252 = !DILocation(line: 143, column: 3, scope: !253)
!253 = distinct !DILexicalBlock(scope: !152, file: !1, line: 141, column: 29)
!254 = !DILocation(line: 145, column: 3, scope: !253)
!255 = !DILocation(line: 146, column: 3, scope: !253)
!256 = !DILocation(line: 148, column: 3, scope: !253)
!257 = !DILocation(line: 149, column: 3, scope: !253)
!258 = !DILocation(line: 151, column: 3, scope: !253)
!259 = !DILocation(line: 152, column: 3, scope: !253)
!260 = !DILocation(line: 154, column: 3, scope: !253)
!261 = !DILocation(line: 155, column: 3, scope: !253)
!262 = !DILocation(line: 157, column: 3, scope: !253)
!263 = !DILocation(line: 158, column: 3, scope: !253)
!264 = !DILocation(line: 162, column: 6, scope: !265)
!265 = distinct !DILexicalBlock(scope: !152, file: !1, line: 162, column: 6)
!266 = !DILocation(line: 162, column: 12, scope: !265)
!267 = !DILocation(line: 162, column: 30, scope: !265)
!268 = !DILocation(line: 162, column: 6, scope: !152)
!269 = !DILocation(line: 163, column: 3, scope: !270)
!270 = distinct !DILexicalBlock(scope: !265, file: !1, line: 162, column: 35)
!271 = !DILocation(line: 164, column: 37, scope: !270)
!272 = !DILocation(line: 164, column: 43, scope: !270)
!273 = !DILocation(line: 164, column: 35, scope: !270)
!274 = !DILocation(line: 164, column: 31, scope: !270)
!275 = !DILocation(line: 164, column: 3, scope: !270)
!276 = !DILocation(line: 165, column: 2, scope: !270)
!277 = !DILocation(line: 167, column: 35, scope: !152)
!278 = !DILocation(line: 167, column: 38, scope: !152)
!279 = !DILocation(line: 167, column: 44, scope: !152)
!280 = !DILocation(line: 167, column: 54, scope: !152)
!281 = !DILocation(line: 167, column: 6, scope: !152)
!282 = !DILocation(line: 167, column: 4, scope: !152)
!283 = !DILocation(line: 168, column: 2, scope: !152)
!284 = !DILocation(line: 169, column: 10, scope: !152)
!285 = !DILocation(line: 169, column: 2, scope: !152)
!286 = !DILocalVariable(name: "f", arg: 1, scope: !126, file: !1, line: 96, type: !129)
!287 = !DILocation(line: 96, column: 58, scope: !126)
!288 = !DILocalVariable(name: "key", arg: 2, scope: !126, file: !1, line: 96, type: !95)
!289 = !DILocation(line: 96, column: 73, scope: !126)
!290 = !DILocalVariable(name: "value", arg: 3, scope: !126, file: !1, line: 97, type: !95)
!291 = !DILocation(line: 97, column: 17, scope: !126)
!292 = !DILocalVariable(name: "data", scope: !126, file: !1, line: 99, type: !22)
!293 = !DILocation(line: 99, column: 22, scope: !126)
!294 = !DILocation(line: 99, column: 51, scope: !126)
!295 = !DILocation(line: 99, column: 54, scope: !126)
!296 = !DILocation(line: 99, column: 29, scope: !126)
!297 = !DILocation(line: 101, column: 13, scope: !298)
!298 = distinct !DILexicalBlock(scope: !126, file: !1, line: 101, column: 6)
!299 = !DILocation(line: 101, column: 6, scope: !298)
!300 = !DILocation(line: 101, column: 33, scope: !298)
!301 = !DILocation(line: 101, column: 6, scope: !126)
!302 = !DILocation(line: 102, column: 7, scope: !303)
!303 = distinct !DILexicalBlock(scope: !304, file: !1, line: 102, column: 7)
!304 = distinct !DILexicalBlock(scope: !298, file: !1, line: 101, column: 39)
!305 = !DILocation(line: 102, column: 13, scope: !303)
!306 = !DILocation(line: 102, column: 7, scope: !304)
!307 = !DILocation(line: 103, column: 4, scope: !303)
!308 = !DILocation(line: 104, column: 19, scope: !309)
!309 = distinct !DILexicalBlock(scope: !303, file: !1, line: 104, column: 12)
!310 = !DILocation(line: 104, column: 12, scope: !309)
!311 = !DILocation(line: 104, column: 35, scope: !309)
!312 = !DILocation(line: 104, column: 12, scope: !303)
!313 = !DILocation(line: 105, column: 4, scope: !309)
!314 = !DILocation(line: 105, column: 10, scope: !309)
!315 = !DILocation(line: 105, column: 22, scope: !309)
!316 = !DILocation(line: 106, column: 19, scope: !317)
!317 = distinct !DILexicalBlock(scope: !309, file: !1, line: 106, column: 12)
!318 = !DILocation(line: 106, column: 12, scope: !317)
!319 = !DILocation(line: 106, column: 34, scope: !317)
!320 = !DILocation(line: 106, column: 12, scope: !309)
!321 = !DILocation(line: 107, column: 4, scope: !317)
!322 = !DILocation(line: 107, column: 10, scope: !317)
!323 = !DILocation(line: 107, column: 22, scope: !317)
!324 = !DILocation(line: 108, column: 19, scope: !325)
!325 = distinct !DILexicalBlock(scope: !317, file: !1, line: 108, column: 12)
!326 = !DILocation(line: 108, column: 12, scope: !325)
!327 = !DILocation(line: 108, column: 33, scope: !325)
!328 = !DILocation(line: 108, column: 12, scope: !317)
!329 = !DILocation(line: 109, column: 4, scope: !325)
!330 = !DILocation(line: 109, column: 10, scope: !325)
!331 = !DILocation(line: 109, column: 22, scope: !325)
!332 = !DILocation(line: 110, column: 19, scope: !333)
!333 = distinct !DILexicalBlock(scope: !325, file: !1, line: 110, column: 12)
!334 = !DILocation(line: 110, column: 12, scope: !333)
!335 = !DILocation(line: 110, column: 34, scope: !333)
!336 = !DILocation(line: 110, column: 12, scope: !325)
!337 = !DILocation(line: 111, column: 4, scope: !333)
!338 = !DILocation(line: 111, column: 10, scope: !333)
!339 = !DILocation(line: 111, column: 22, scope: !333)
!340 = !DILocation(line: 112, column: 19, scope: !341)
!341 = distinct !DILexicalBlock(scope: !333, file: !1, line: 112, column: 12)
!342 = !DILocation(line: 112, column: 12, scope: !341)
!343 = !DILocation(line: 112, column: 34, scope: !341)
!344 = !DILocation(line: 112, column: 12, scope: !333)
!345 = !DILocation(line: 113, column: 4, scope: !341)
!346 = !DILocation(line: 113, column: 10, scope: !341)
!347 = !DILocation(line: 113, column: 22, scope: !341)
!348 = !DILocation(line: 115, column: 4, scope: !341)
!349 = !DILocation(line: 116, column: 3, scope: !304)
!350 = !DILocation(line: 117, column: 20, scope: !351)
!351 = distinct !DILexicalBlock(scope: !298, file: !1, line: 117, column: 13)
!352 = !DILocation(line: 117, column: 13, scope: !351)
!353 = !DILocation(line: 117, column: 46, scope: !351)
!354 = !DILocation(line: 117, column: 13, scope: !298)
!355 = !DILocation(line: 118, column: 7, scope: !356)
!356 = distinct !DILexicalBlock(scope: !357, file: !1, line: 118, column: 7)
!357 = distinct !DILexicalBlock(scope: !351, file: !1, line: 117, column: 52)
!358 = !DILocation(line: 118, column: 13, scope: !356)
!359 = !DILocation(line: 118, column: 21, scope: !356)
!360 = !DILocation(line: 118, column: 26, scope: !361)
!361 = !DILexicalBlockFile(scope: !356, file: !1, discriminator: 1)
!362 = !DILocation(line: 118, column: 35, scope: !361)
!363 = !DILocation(line: 118, column: 42, scope: !361)
!364 = !DILocation(line: 118, column: 45, scope: !365)
!365 = !DILexicalBlockFile(scope: !356, file: !1, discriminator: 2)
!366 = !DILocation(line: 118, column: 54, scope: !365)
!367 = !DILocation(line: 118, column: 62, scope: !365)
!368 = !DILocation(line: 119, column: 7, scope: !356)
!369 = !DILocation(line: 119, column: 16, scope: !356)
!370 = !DILocation(line: 118, column: 7, scope: !371)
!371 = !DILexicalBlockFile(scope: !357, file: !1, discriminator: 3)
!372 = !DILocation(line: 120, column: 4, scope: !356)
!373 = !DILocation(line: 121, column: 29, scope: !357)
!374 = !DILocation(line: 121, column: 38, scope: !357)
!375 = !DILocation(line: 121, column: 3, scope: !357)
!376 = !DILocation(line: 121, column: 9, scope: !357)
!377 = !DILocation(line: 121, column: 27, scope: !357)
!378 = !DILocation(line: 122, column: 3, scope: !357)
!379 = !DILocation(line: 127, column: 2, scope: !126)
!380 = !DILocation(line: 128, column: 1, scope: !126)
!381 = !DILocalVariable(name: "f", arg: 1, scope: !153, file: !1, line: 173, type: !129)
!382 = !DILocation(line: 173, column: 56, scope: !153)
!383 = !DILocalVariable(name: "buff", arg: 2, scope: !153, file: !1, line: 174, type: !58)
!384 = !DILocation(line: 174, column: 17, scope: !153)
!385 = !DILocalVariable(name: "length", arg: 3, scope: !153, file: !1, line: 174, type: !60)
!386 = !DILocation(line: 174, column: 30, scope: !153)
!387 = !DILocalVariable(name: "data", scope: !153, file: !1, line: 176, type: !22)
!388 = !DILocation(line: 176, column: 22, scope: !153)
!389 = !DILocation(line: 176, column: 51, scope: !153)
!390 = !DILocation(line: 176, column: 54, scope: !153)
!391 = !DILocation(line: 176, column: 29, scope: !153)
!392 = !DILocation(line: 178, column: 39, scope: !153)
!393 = !DILocation(line: 178, column: 42, scope: !153)
!394 = !DILocation(line: 178, column: 48, scope: !153)
!395 = !DILocation(line: 178, column: 55, scope: !153)
!396 = !DILocation(line: 178, column: 61, scope: !153)
!397 = !DILocation(line: 178, column: 9, scope: !153)
!398 = !DILocation(line: 178, column: 2, scope: !153)
!399 = !DILocalVariable(name: "f", arg: 1, scope: !154, file: !1, line: 182, type: !129)
!400 = !DILocation(line: 182, column: 56, scope: !154)
!401 = !DILocalVariable(name: "data", scope: !154, file: !1, line: 184, type: !22)
!402 = !DILocation(line: 184, column: 22, scope: !154)
!403 = !DILocation(line: 184, column: 51, scope: !154)
!404 = !DILocation(line: 184, column: 54, scope: !154)
!405 = !DILocation(line: 184, column: 29, scope: !154)
!406 = !DILocation(line: 186, column: 39, scope: !154)
!407 = !DILocation(line: 186, column: 42, scope: !154)
!408 = !DILocation(line: 186, column: 48, scope: !154)
!409 = !DILocation(line: 186, column: 9, scope: !154)
!410 = !DILocation(line: 186, column: 2, scope: !154)
!411 = !DILocalVariable(name: "f", arg: 1, scope: !155, file: !1, line: 190, type: !129)
!412 = !DILocation(line: 190, column: 55, scope: !155)
!413 = !DILocalVariable(name: "data", scope: !155, file: !1, line: 192, type: !22)
!414 = !DILocation(line: 192, column: 22, scope: !155)
!415 = !DILocation(line: 192, column: 51, scope: !155)
!416 = !DILocation(line: 192, column: 54, scope: !155)
!417 = !DILocation(line: 192, column: 29, scope: !155)
!418 = !DILocation(line: 194, column: 31, scope: !155)
!419 = !DILocation(line: 194, column: 37, scope: !155)
!420 = !DILocation(line: 194, column: 2, scope: !155)
!421 = !DILocation(line: 195, column: 7, scope: !155)
!422 = !DILocation(line: 195, column: 2, scope: !155)
!423 = !DILocation(line: 196, column: 2, scope: !155)
