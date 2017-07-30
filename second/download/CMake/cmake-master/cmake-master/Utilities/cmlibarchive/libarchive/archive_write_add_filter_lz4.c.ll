; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_lz4.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.private_data = type { i32, i16, %struct.archive_write_program_data* }
%struct.archive_write_program_data = type opaque

@.str = private unnamed_addr constant [29 x i8] c"archive_write_add_filter_lz4\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Out of memory\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"lz4\00", align 1
@.str.3 = private unnamed_addr constant [27 x i8] c"Using external lz4 program\00", align 1
@.str.4 = private unnamed_addr constant [18 x i8] c"compression-level\00", align 1
@.str.5 = private unnamed_addr constant [44 x i8] c"High compression not included in this build\00", align 1
@.str.6 = private unnamed_addr constant [16 x i8] c"stream-checksum\00", align 1
@.str.7 = private unnamed_addr constant [15 x i8] c"block-checksum\00", align 1
@.str.8 = private unnamed_addr constant [11 x i8] c"block-size\00", align 1
@.str.9 = private unnamed_addr constant [17 x i8] c"block-dependence\00", align 1
@.str.10 = private unnamed_addr constant [13 x i8] c"lz4 -z -q -q\00", align 1
@.str.11 = private unnamed_addr constant [3 x i8] c" -\00", align 1
@.str.12 = private unnamed_addr constant [4 x i8] c" -B\00", align 1
@.str.13 = private unnamed_addr constant [5 x i8] c" -BX\00", align 1
@.str.14 = private unnamed_addr constant [16 x i8] c" --no-frame-crc\00", align 1
@.str.15 = private unnamed_addr constant [5 x i8] c" -BD\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_lz4(%struct.archive* %_a) #0 !dbg !207 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !216, metadata !217), !dbg !218
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !219, metadata !217), !dbg !220
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !221
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !222
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !220
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !223, metadata !217), !dbg !224
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !225
  %call = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %2), !dbg !226
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !224
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !227, metadata !217), !dbg !228
  br label %do.body, !dbg !229

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !230, metadata !217), !dbg !232
  %3 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !233
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %3, i32 0, i32 0, !dbg !233
  %call1 = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1329217314, i32 1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str, i32 0, i32 0)), !dbg !233
  store i32 %call1, i32* %magic_test, align 4, !dbg !233
  %4 = load i32, i32* %magic_test, align 4, !dbg !233
  %cmp = icmp eq i32 %4, -30, !dbg !233
  br i1 %cmp, label %if.then, label %if.end, !dbg !233

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !235
  br label %return, !dbg !235

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !238

do.end:                                           ; preds = %if.end
  %call2 = call noalias i8* @calloc(i64 1, i64 16) #5, !dbg !240
  %5 = bitcast i8* %call2 to %struct.private_data*, !dbg !240
  store %struct.private_data* %5, %struct.private_data** %data, align 8, !dbg !241
  %6 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !242
  %cmp3 = icmp eq %struct.private_data* %6, null, !dbg !244
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !245

if.then4:                                         ; preds = %do.end
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !246
  %archive5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !248
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive5, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.1, i32 0, i32 0)), !dbg !249
  store i32 -30, i32* %retval, align 4, !dbg !250
  br label %return, !dbg !250

if.end6:                                          ; preds = %do.end
  %8 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !251
  %compression_level = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 0, !dbg !252
  store i32 1, i32* %compression_level, align 8, !dbg !253
  %9 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !254
  %version_number = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 1, !dbg !255
  %bf.load = load i16, i16* %version_number, align 4, !dbg !256
  %bf.clear = and i16 %bf.load, -3, !dbg !256
  %bf.set = or i16 %bf.clear, 2, !dbg !256
  store i16 %bf.set, i16* %version_number, align 4, !dbg !256
  %10 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !257
  %block_independence = getelementptr inbounds %struct.private_data, %struct.private_data* %10, i32 0, i32 1, !dbg !258
  %bf.load7 = load i16, i16* %block_independence, align 4, !dbg !259
  %bf.clear8 = and i16 %bf.load7, -5, !dbg !259
  %bf.set9 = or i16 %bf.clear8, 4, !dbg !259
  store i16 %bf.set9, i16* %block_independence, align 4, !dbg !259
  %11 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !260
  %block_checksum = getelementptr inbounds %struct.private_data, %struct.private_data* %11, i32 0, i32 1, !dbg !261
  %bf.load10 = load i16, i16* %block_checksum, align 4, !dbg !262
  %bf.clear11 = and i16 %bf.load10, -9, !dbg !262
  store i16 %bf.clear11, i16* %block_checksum, align 4, !dbg !262
  %12 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !263
  %stream_size = getelementptr inbounds %struct.private_data, %struct.private_data* %12, i32 0, i32 1, !dbg !264
  %bf.load12 = load i16, i16* %stream_size, align 4, !dbg !265
  %bf.clear13 = and i16 %bf.load12, -17, !dbg !265
  store i16 %bf.clear13, i16* %stream_size, align 4, !dbg !265
  %13 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !266
  %stream_checksum = getelementptr inbounds %struct.private_data, %struct.private_data* %13, i32 0, i32 1, !dbg !267
  %bf.load14 = load i16, i16* %stream_checksum, align 4, !dbg !268
  %bf.clear15 = and i16 %bf.load14, -33, !dbg !268
  %bf.set16 = or i16 %bf.clear15, 32, !dbg !268
  store i16 %bf.set16, i16* %stream_checksum, align 4, !dbg !268
  %14 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !269
  %preset_dictionary = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 1, !dbg !270
  %bf.load17 = load i16, i16* %preset_dictionary, align 4, !dbg !271
  %bf.clear18 = and i16 %bf.load17, -65, !dbg !271
  store i16 %bf.clear18, i16* %preset_dictionary, align 4, !dbg !271
  %15 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !272
  %block_maximum_size = getelementptr inbounds %struct.private_data, %struct.private_data* %15, i32 0, i32 1, !dbg !273
  %bf.load19 = load i16, i16* %block_maximum_size, align 4, !dbg !274
  %bf.clear20 = and i16 %bf.load19, -897, !dbg !274
  %bf.set21 = or i16 %bf.clear20, 896, !dbg !274
  store i16 %bf.set21, i16* %block_maximum_size, align 4, !dbg !274
  %16 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !275
  %17 = bitcast %struct.private_data* %16 to i8*, !dbg !275
  %18 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !276
  %data22 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %18, i32 0, i32 8, !dbg !277
  store i8* %17, i8** %data22, align 8, !dbg !278
  %19 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !279
  %options = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %19, i32 0, i32 3, !dbg !280
  store i32 (%struct.archive_write_filter*, i8*, i8*)* @archive_filter_lz4_options, i32 (%struct.archive_write_filter*, i8*, i8*)** %options, align 8, !dbg !281
  %20 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !282
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %20, i32 0, i32 6, !dbg !283
  store i32 (%struct.archive_write_filter*)* @archive_filter_lz4_close, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !284
  %21 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !285
  %free = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %21, i32 0, i32 7, !dbg !286
  store i32 (%struct.archive_write_filter*)* @archive_filter_lz4_free, i32 (%struct.archive_write_filter*)** %free, align 8, !dbg !287
  %22 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !288
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %22, i32 0, i32 4, !dbg !289
  store i32 (%struct.archive_write_filter*)* @archive_filter_lz4_open, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !290
  %23 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !291
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %23, i32 0, i32 10, !dbg !292
  store i32 13, i32* %code, align 8, !dbg !293
  %24 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !294
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %24, i32 0, i32 9, !dbg !295
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8** %name, align 8, !dbg !296
  %call23 = call %struct.archive_write_program_data* @__archive_write_program_allocate(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0)), !dbg !297
  %25 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !298
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %25, i32 0, i32 2, !dbg !299
  store %struct.archive_write_program_data* %call23, %struct.archive_write_program_data** %pdata, align 8, !dbg !300
  %26 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !301
  %pdata24 = getelementptr inbounds %struct.private_data, %struct.private_data* %26, i32 0, i32 2, !dbg !303
  %27 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata24, align 8, !dbg !303
  %cmp25 = icmp eq %struct.archive_write_program_data* %27, null, !dbg !304
  br i1 %cmp25, label %if.then26, label %if.end28, !dbg !305

if.then26:                                        ; preds = %if.end6
  %28 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !306
  %29 = bitcast %struct.private_data* %28 to i8*, !dbg !306
  call void @free(i8* %29) #5, !dbg !308
  %30 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !309
  %archive27 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %30, i32 0, i32 0, !dbg !310
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive27, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.1, i32 0, i32 0)), !dbg !311
  store i32 -30, i32* %retval, align 4, !dbg !312
  br label %return, !dbg !312

if.end28:                                         ; preds = %if.end6
  %31 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !313
  %compression_level29 = getelementptr inbounds %struct.private_data, %struct.private_data* %31, i32 0, i32 0, !dbg !314
  store i32 0, i32* %compression_level29, align 8, !dbg !315
  %32 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !316
  %archive30 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %32, i32 0, i32 0, !dbg !317
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive30, i32 -1, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.3, i32 0, i32 0)), !dbg !318
  store i32 -20, i32* %retval, align 4, !dbg !319
  br label %return, !dbg !319

return:                                           ; preds = %if.end28, %if.then26, %if.then4, %if.then
  %33 = load i32, i32* %retval, align 4, !dbg !320
  ret i32 %33, !dbg !320
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive*) #2

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_lz4_options(%struct.archive_write_filter* %f, i8* %key, i8* %value) #0 !dbg !208 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %data = alloca %struct.private_data*, align 8
  %val = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !321, metadata !217), !dbg !322
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !323, metadata !217), !dbg !324
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !325, metadata !217), !dbg !326
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !327, metadata !217), !dbg !328
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !329
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !330
  %1 = load i8*, i8** %data1, align 8, !dbg !330
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !331
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !328
  %3 = load i8*, i8** %key.addr, align 8, !dbg !332
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.4, i32 0, i32 0)) #6, !dbg !334
  %cmp = icmp eq i32 %call, 0, !dbg !335
  br i1 %cmp, label %if.then, label %if.end17, !dbg !336

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %val, metadata !337, metadata !217), !dbg !339
  %4 = load i8*, i8** %value.addr, align 8, !dbg !340
  %cmp2 = icmp eq i8* %4, null, !dbg !342
  br i1 %cmp2, label %if.then12, label %lor.lhs.false, !dbg !343

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %value.addr, align 8, !dbg !344
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !344
  %6 = load i8, i8* %arrayidx, align 1, !dbg !344
  %conv = sext i8 %6 to i32, !dbg !344
  %sub = sub nsw i32 %conv, 48, !dbg !346
  store i32 %sub, i32* %val, align 4, !dbg !347
  %cmp3 = icmp sge i32 %sub, 1, !dbg !348
  br i1 %cmp3, label %land.lhs.true, label %if.then12, !dbg !349

land.lhs.true:                                    ; preds = %lor.lhs.false
  %7 = load i32, i32* %val, align 4, !dbg !350
  %cmp5 = icmp sle i32 %7, 9, !dbg !352
  br i1 %cmp5, label %lor.lhs.false7, label %if.then12, !dbg !353

lor.lhs.false7:                                   ; preds = %land.lhs.true
  %8 = load i8*, i8** %value.addr, align 8, !dbg !354
  %arrayidx8 = getelementptr inbounds i8, i8* %8, i64 1, !dbg !354
  %9 = load i8, i8* %arrayidx8, align 1, !dbg !354
  %conv9 = sext i8 %9 to i32, !dbg !354
  %cmp10 = icmp ne i32 %conv9, 0, !dbg !355
  br i1 %cmp10, label %if.then12, label %if.end, !dbg !356

if.then12:                                        ; preds = %lor.lhs.false7, %land.lhs.true, %lor.lhs.false, %if.then
  store i32 -20, i32* %retval, align 4, !dbg !358
  br label %return, !dbg !358

if.end:                                           ; preds = %lor.lhs.false7
  %10 = load i32, i32* %val, align 4, !dbg !359
  %cmp13 = icmp sge i32 %10, 3, !dbg !361
  br i1 %cmp13, label %if.then15, label %if.end16, !dbg !362

if.then15:                                        ; preds = %if.end
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !363
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 1, !dbg !365
  %12 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !365
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %12, i32 22, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.5, i32 0, i32 0)), !dbg !366
  store i32 -30, i32* %retval, align 4, !dbg !367
  br label %return, !dbg !367

if.end16:                                         ; preds = %if.end
  %13 = load i32, i32* %val, align 4, !dbg !368
  %14 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !369
  %compression_level = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 0, !dbg !370
  store i32 %13, i32* %compression_level, align 8, !dbg !371
  store i32 0, i32* %retval, align 4, !dbg !372
  br label %return, !dbg !372

if.end17:                                         ; preds = %entry
  %15 = load i8*, i8** %key.addr, align 8, !dbg !373
  %call18 = call i32 @strcmp(i8* %15, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.6, i32 0, i32 0)) #6, !dbg !375
  %cmp19 = icmp eq i32 %call18, 0, !dbg !376
  br i1 %cmp19, label %if.then21, label %if.end24, !dbg !377

if.then21:                                        ; preds = %if.end17
  %16 = load i8*, i8** %value.addr, align 8, !dbg !378
  %cmp22 = icmp ne i8* %16, null, !dbg !380
  %conv23 = zext i1 %cmp22 to i32, !dbg !380
  %17 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !381
  %stream_checksum = getelementptr inbounds %struct.private_data, %struct.private_data* %17, i32 0, i32 1, !dbg !382
  %18 = trunc i32 %conv23 to i16, !dbg !383
  %bf.load = load i16, i16* %stream_checksum, align 4, !dbg !383
  %bf.value = and i16 %18, 1, !dbg !383
  %bf.shl = shl i16 %bf.value, 5, !dbg !383
  %bf.clear = and i16 %bf.load, -33, !dbg !383
  %bf.set = or i16 %bf.clear, %bf.shl, !dbg !383
  store i16 %bf.set, i16* %stream_checksum, align 4, !dbg !383
  %bf.result.cast = zext i16 %bf.value to i32, !dbg !383
  store i32 0, i32* %retval, align 4, !dbg !384
  br label %return, !dbg !384

if.end24:                                         ; preds = %if.end17
  %19 = load i8*, i8** %key.addr, align 8, !dbg !385
  %call25 = call i32 @strcmp(i8* %19, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.7, i32 0, i32 0)) #6, !dbg !387
  %cmp26 = icmp eq i32 %call25, 0, !dbg !388
  br i1 %cmp26, label %if.then28, label %if.end37, !dbg !389

if.then28:                                        ; preds = %if.end24
  %20 = load i8*, i8** %value.addr, align 8, !dbg !390
  %cmp29 = icmp ne i8* %20, null, !dbg !392
  %conv30 = zext i1 %cmp29 to i32, !dbg !392
  %21 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !393
  %block_checksum = getelementptr inbounds %struct.private_data, %struct.private_data* %21, i32 0, i32 1, !dbg !394
  %22 = trunc i32 %conv30 to i16, !dbg !395
  %bf.load31 = load i16, i16* %block_checksum, align 4, !dbg !395
  %bf.value32 = and i16 %22, 1, !dbg !395
  %bf.shl33 = shl i16 %bf.value32, 3, !dbg !395
  %bf.clear34 = and i16 %bf.load31, -9, !dbg !395
  %bf.set35 = or i16 %bf.clear34, %bf.shl33, !dbg !395
  store i16 %bf.set35, i16* %block_checksum, align 4, !dbg !395
  %bf.result.cast36 = zext i16 %bf.value32 to i32, !dbg !395
  store i32 0, i32* %retval, align 4, !dbg !396
  br label %return, !dbg !396

if.end37:                                         ; preds = %if.end24
  %23 = load i8*, i8** %key.addr, align 8, !dbg !397
  %call38 = call i32 @strcmp(i8* %23, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.8, i32 0, i32 0)) #6, !dbg !399
  %cmp39 = icmp eq i32 %call38, 0, !dbg !400
  br i1 %cmp39, label %if.then41, label %if.end70, !dbg !401

if.then41:                                        ; preds = %if.end37
  %24 = load i8*, i8** %value.addr, align 8, !dbg !402
  %cmp42 = icmp eq i8* %24, null, !dbg !405
  br i1 %cmp42, label %if.then59, label %lor.lhs.false44, !dbg !406

lor.lhs.false44:                                  ; preds = %if.then41
  %25 = load i8*, i8** %value.addr, align 8, !dbg !407
  %arrayidx45 = getelementptr inbounds i8, i8* %25, i64 0, !dbg !407
  %26 = load i8, i8* %arrayidx45, align 1, !dbg !407
  %conv46 = sext i8 %26 to i32, !dbg !407
  %cmp47 = icmp sge i32 %conv46, 52, !dbg !409
  br i1 %cmp47, label %land.lhs.true49, label %if.then59, !dbg !410

land.lhs.true49:                                  ; preds = %lor.lhs.false44
  %27 = load i8*, i8** %value.addr, align 8, !dbg !411
  %arrayidx50 = getelementptr inbounds i8, i8* %27, i64 0, !dbg !411
  %28 = load i8, i8* %arrayidx50, align 1, !dbg !411
  %conv51 = sext i8 %28 to i32, !dbg !411
  %cmp52 = icmp sle i32 %conv51, 55, !dbg !413
  br i1 %cmp52, label %lor.lhs.false54, label %if.then59, !dbg !414

lor.lhs.false54:                                  ; preds = %land.lhs.true49
  %29 = load i8*, i8** %value.addr, align 8, !dbg !415
  %arrayidx55 = getelementptr inbounds i8, i8* %29, i64 1, !dbg !415
  %30 = load i8, i8* %arrayidx55, align 1, !dbg !415
  %conv56 = sext i8 %30 to i32, !dbg !415
  %cmp57 = icmp ne i32 %conv56, 0, !dbg !416
  br i1 %cmp57, label %if.then59, label %if.end60, !dbg !417

if.then59:                                        ; preds = %lor.lhs.false54, %land.lhs.true49, %lor.lhs.false44, %if.then41
  store i32 -20, i32* %retval, align 4, !dbg !419
  br label %return, !dbg !419

if.end60:                                         ; preds = %lor.lhs.false54
  %31 = load i8*, i8** %value.addr, align 8, !dbg !420
  %arrayidx61 = getelementptr inbounds i8, i8* %31, i64 0, !dbg !420
  %32 = load i8, i8* %arrayidx61, align 1, !dbg !420
  %conv62 = sext i8 %32 to i32, !dbg !420
  %sub63 = sub nsw i32 %conv62, 48, !dbg !421
  %33 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !422
  %block_maximum_size = getelementptr inbounds %struct.private_data, %struct.private_data* %33, i32 0, i32 1, !dbg !423
  %34 = trunc i32 %sub63 to i16, !dbg !424
  %bf.load64 = load i16, i16* %block_maximum_size, align 4, !dbg !424
  %bf.value65 = and i16 %34, 7, !dbg !424
  %bf.shl66 = shl i16 %bf.value65, 7, !dbg !424
  %bf.clear67 = and i16 %bf.load64, -897, !dbg !424
  %bf.set68 = or i16 %bf.clear67, %bf.shl66, !dbg !424
  store i16 %bf.set68, i16* %block_maximum_size, align 4, !dbg !424
  %bf.result.cast69 = zext i16 %bf.value65 to i32, !dbg !424
  store i32 0, i32* %retval, align 4, !dbg !425
  br label %return, !dbg !425

if.end70:                                         ; preds = %if.end37
  %35 = load i8*, i8** %key.addr, align 8, !dbg !426
  %call71 = call i32 @strcmp(i8* %35, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.9, i32 0, i32 0)) #6, !dbg !428
  %cmp72 = icmp eq i32 %call71, 0, !dbg !429
  br i1 %cmp72, label %if.then74, label %if.end83, !dbg !430

if.then74:                                        ; preds = %if.end70
  %36 = load i8*, i8** %value.addr, align 8, !dbg !431
  %cmp75 = icmp eq i8* %36, null, !dbg !433
  %conv76 = zext i1 %cmp75 to i32, !dbg !433
  %37 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !434
  %block_independence = getelementptr inbounds %struct.private_data, %struct.private_data* %37, i32 0, i32 1, !dbg !435
  %38 = trunc i32 %conv76 to i16, !dbg !436
  %bf.load77 = load i16, i16* %block_independence, align 4, !dbg !436
  %bf.value78 = and i16 %38, 1, !dbg !436
  %bf.shl79 = shl i16 %bf.value78, 2, !dbg !436
  %bf.clear80 = and i16 %bf.load77, -5, !dbg !436
  %bf.set81 = or i16 %bf.clear80, %bf.shl79, !dbg !436
  store i16 %bf.set81, i16* %block_independence, align 4, !dbg !436
  %bf.result.cast82 = zext i16 %bf.value78 to i32, !dbg !436
  store i32 0, i32* %retval, align 4, !dbg !437
  br label %return, !dbg !437

if.end83:                                         ; preds = %if.end70
  store i32 -20, i32* %retval, align 4, !dbg !438
  br label %return, !dbg !438

return:                                           ; preds = %if.end83, %if.then74, %if.end60, %if.then59, %if.then28, %if.then21, %if.end16, %if.then15, %if.then12
  %39 = load i32, i32* %retval, align 4, !dbg !439
  ret i32 %39, !dbg !439
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_lz4_close(%struct.archive_write_filter* %f) #0 !dbg !211 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !440, metadata !217), !dbg !441
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !442, metadata !217), !dbg !443
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !444
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !445
  %1 = load i8*, i8** %data1, align 8, !dbg !445
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !446
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !443
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !447
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !448
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 2, !dbg !449
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !449
  %call = call i32 @__archive_write_program_close(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5), !dbg !450
  ret i32 %call, !dbg !451
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_lz4_free(%struct.archive_write_filter* %f) #0 !dbg !212 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !452, metadata !217), !dbg !453
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !454, metadata !217), !dbg !455
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !456
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !457
  %1 = load i8*, i8** %data1, align 8, !dbg !457
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !458
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !455
  %3 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !459
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 2, !dbg !460
  %4 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !460
  %call = call i32 @__archive_write_program_free(%struct.archive_write_program_data* %4), !dbg !461
  %5 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !462
  %6 = bitcast %struct.private_data* %5 to i8*, !dbg !462
  call void @free(i8* %6) #5, !dbg !463
  ret i32 0, !dbg !464
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_lz4_open(%struct.archive_write_filter* %f) #0 !dbg !209 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  %as = alloca %struct.archive_string, align 8
  %r = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !465, metadata !217), !dbg !466
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !467, metadata !217), !dbg !468
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !469
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !470
  %1 = load i8*, i8** %data1, align 8, !dbg !470
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !471
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !468
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !472, metadata !217), !dbg !473
  call void @llvm.dbg.declare(metadata i32* %r, metadata !474, metadata !217), !dbg !475
  br label %do.body, !dbg !476

do.body:                                          ; preds = %entry
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !477
  store i8* null, i8** %s, align 8, !dbg !477
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !477
  store i64 0, i64* %length, align 8, !dbg !477
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !477
  store i64 0, i64* %buffer_length, align 8, !dbg !477
  br label %do.end, !dbg !477

do.end:                                           ; preds = %do.body
  %length2 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !480
  store i64 0, i64* %length2, align 8, !dbg !480
  %call = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.10, i32 0, i32 0), i64 12), !dbg !480
  %3 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !481
  %compression_level = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 0, !dbg !483
  %4 = load i32, i32* %compression_level, align 8, !dbg !483
  %cmp = icmp sgt i32 %4, 0, !dbg !484
  br i1 %cmp, label %if.then, label %if.end, !dbg !485

if.then:                                          ; preds = %do.end
  %call3 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0)), !dbg !486
  %5 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !488
  %compression_level4 = getelementptr inbounds %struct.private_data, %struct.private_data* %5, i32 0, i32 0, !dbg !489
  %6 = load i32, i32* %compression_level4, align 8, !dbg !489
  %add = add nsw i32 48, %6, !dbg !490
  %conv = trunc i32 %add to i8, !dbg !491
  %call5 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext %conv), !dbg !492
  br label %if.end, !dbg !493

if.end:                                           ; preds = %if.then, %do.end
  %call6 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.12, i32 0, i32 0)), !dbg !494
  %7 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !495
  %block_maximum_size = getelementptr inbounds %struct.private_data, %struct.private_data* %7, i32 0, i32 1, !dbg !496
  %bf.load = load i16, i16* %block_maximum_size, align 4, !dbg !496
  %bf.lshr = lshr i16 %bf.load, 7, !dbg !496
  %bf.clear = and i16 %bf.lshr, 7, !dbg !496
  %bf.cast = zext i16 %bf.clear to i32, !dbg !496
  %add7 = add nsw i32 48, %bf.cast, !dbg !497
  %conv8 = trunc i32 %add7 to i8, !dbg !498
  %call9 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext %conv8), !dbg !499
  %8 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !500
  %block_checksum = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 1, !dbg !502
  %bf.load10 = load i16, i16* %block_checksum, align 4, !dbg !502
  %bf.lshr11 = lshr i16 %bf.load10, 3, !dbg !502
  %bf.clear12 = and i16 %bf.lshr11, 1, !dbg !502
  %bf.cast13 = zext i16 %bf.clear12 to i32, !dbg !502
  %tobool = icmp ne i32 %bf.cast13, 0, !dbg !500
  br i1 %tobool, label %if.then14, label %if.end16, !dbg !503

if.then14:                                        ; preds = %if.end
  %call15 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0)), !dbg !504
  br label %if.end16, !dbg !504

if.end16:                                         ; preds = %if.then14, %if.end
  %9 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !505
  %stream_checksum = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 1, !dbg !507
  %bf.load17 = load i16, i16* %stream_checksum, align 4, !dbg !507
  %bf.lshr18 = lshr i16 %bf.load17, 5, !dbg !507
  %bf.clear19 = and i16 %bf.lshr18, 1, !dbg !507
  %bf.cast20 = zext i16 %bf.clear19 to i32, !dbg !507
  %cmp21 = icmp eq i32 %bf.cast20, 0, !dbg !508
  br i1 %cmp21, label %if.then23, label %if.end25, !dbg !509

if.then23:                                        ; preds = %if.end16
  %call24 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.14, i32 0, i32 0)), !dbg !510
  br label %if.end25, !dbg !510

if.end25:                                         ; preds = %if.then23, %if.end16
  %10 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !511
  %block_independence = getelementptr inbounds %struct.private_data, %struct.private_data* %10, i32 0, i32 1, !dbg !513
  %bf.load26 = load i16, i16* %block_independence, align 4, !dbg !513
  %bf.lshr27 = lshr i16 %bf.load26, 2, !dbg !513
  %bf.clear28 = and i16 %bf.lshr27, 1, !dbg !513
  %bf.cast29 = zext i16 %bf.clear28 to i32, !dbg !513
  %cmp30 = icmp eq i32 %bf.cast29, 0, !dbg !514
  br i1 %cmp30, label %if.then32, label %if.end34, !dbg !515

if.then32:                                        ; preds = %if.end25
  %call33 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %as, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.15, i32 0, i32 0)), !dbg !516
  br label %if.end34, !dbg !516

if.end34:                                         ; preds = %if.then32, %if.end25
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !517
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 5, !dbg !518
  store i32 (%struct.archive_write_filter*, i8*, i64)* @archive_filter_lz4_write, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !519
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !520
  %13 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !521
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %13, i32 0, i32 2, !dbg !522
  %14 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !522
  %s35 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !523
  %15 = load i8*, i8** %s35, align 8, !dbg !523
  %call36 = call i32 @__archive_write_program_open(%struct.archive_write_filter* %12, %struct.archive_write_program_data* %14, i8* %15), !dbg !524
  store i32 %call36, i32* %r, align 4, !dbg !525
  call void @archive_string_free(%struct.archive_string* %as), !dbg !526
  %16 = load i32, i32* %r, align 4, !dbg !527
  ret i32 %16, !dbg !528
}

declare %struct.archive_write_program_data* @__archive_write_program_allocate(i8*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare %struct.archive_string* @archive_strcat(%struct.archive_string*, i8*) #2

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_filter_lz4_write(%struct.archive_write_filter* %f, i8* %buff, i64 %length) #0 !dbg !210 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !529, metadata !217), !dbg !530
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !531, metadata !217), !dbg !532
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !533, metadata !217), !dbg !534
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !535, metadata !217), !dbg !536
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !537
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !538
  %1 = load i8*, i8** %data1, align 8, !dbg !538
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !539
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !536
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !540
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !541
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 2, !dbg !542
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !542
  %6 = load i8*, i8** %buff.addr, align 8, !dbg !543
  %7 = load i64, i64* %length.addr, align 8, !dbg !544
  %call = call i32 @__archive_write_program_write(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5, i8* %6, i64 %7), !dbg !545
  ret i32 %call, !dbg !546
}

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
!llvm.module.flags = !{!213, !214}
!llvm.ident = !{!215}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !206)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_lz4.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !123, !191}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !6, line: 72, size: 2816, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !117, !118, !124, !130, !133, !134, !135, !136, !162, !163, !164, !165, !169, !173, !174, !178, !182, !183, !184, !185, !190}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 73, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24}
!23 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!23, !24, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !24, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 102, baseType: !40)
!39 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !24, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!23, !24, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !24, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !24, !23}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!23, !24, !23}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !24, !23}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !23, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !23, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !23, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !23, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 76, baseType: !23, size: 32, align: 32, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 77, baseType: !52, size: 64, align: 64, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 78, baseType: !52, size: 64, align: 64, offset: 1408)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !5, file: !6, line: 81, baseType: !114, size: 64, align: 64, offset: 1472)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !116)
!116 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !5, file: !6, line: 82, baseType: !45, size: 64, align: 64, offset: 1536)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !5, file: !6, line: 85, baseType: !119, size: 64, align: 64, offset: 1600)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !121)
!121 = !DISubroutineType(types: !122)
!122 = !{!23, !24, !123}
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !5, file: !6, line: 86, baseType: !125, size: 64, align: 64, offset: 1664)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !126, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !32, line: 237, baseType: !127)
!127 = !DISubroutineType(types: !128)
!128 = !{!129, !24, !123, !43, !45}
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !5, file: !6, line: 87, baseType: !131, size: 64, align: 64, offset: 1728)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !121)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !5, file: !6, line: 88, baseType: !123, size: 64, align: 64, offset: 1792)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !5, file: !6, line: 96, baseType: !23, size: 32, align: 32, offset: 1856)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !5, file: !6, line: 97, baseType: !23, size: 32, align: 32, offset: 1888)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !5, file: !6, line: 102, baseType: !137, size: 64, align: 64, offset: 1920)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !6, line: 43, size: 768, align: 64, elements: !139)
!139 = !{!140, !141, !142, !143, !147, !151, !155, !156, !157, !158, !159, !160, !161}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !138, file: !6, line: 44, baseType: !52, size: 64, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !138, file: !6, line: 45, baseType: !24, size: 64, align: 64, offset: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !138, file: !6, line: 46, baseType: !137, size: 64, align: 64, offset: 128)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !138, file: !6, line: 47, baseType: !144, size: 64, align: 64, offset: 192)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DISubroutineType(types: !146)
!146 = !{!23, !137, !80, !80}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !138, file: !6, line: 49, baseType: !148, size: 64, align: 64, offset: 256)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!149 = !DISubroutineType(types: !150)
!150 = !{!23, !137}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !138, file: !6, line: 50, baseType: !152, size: 64, align: 64, offset: 320)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DISubroutineType(types: !154)
!154 = !{!23, !137, !43, !45}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !138, file: !6, line: 51, baseType: !148, size: 64, align: 64, offset: 384)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !138, file: !6, line: 52, baseType: !148, size: 64, align: 64, offset: 448)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !138, file: !6, line: 53, baseType: !123, size: 64, align: 64, offset: 512)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !138, file: !6, line: 54, baseType: !80, size: 64, align: 64, offset: 576)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !138, file: !6, line: 55, baseType: !23, size: 32, align: 32, offset: 640)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !138, file: !6, line: 56, baseType: !23, size: 32, align: 32, offset: 672)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !138, file: !6, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !5, file: !6, line: 103, baseType: !137, size: 64, align: 64, offset: 1984)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !5, file: !6, line: 109, baseType: !123, size: 64, align: 64, offset: 2048)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !5, file: !6, line: 110, baseType: !80, size: 64, align: 64, offset: 2112)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !5, file: !6, line: 111, baseType: !166, size: 64, align: 64, offset: 2176)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DISubroutineType(types: !168)
!168 = !{!23, !4}
!169 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !5, file: !6, line: 112, baseType: !170, size: 64, align: 64, offset: 2240)
!170 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!171 = !DISubroutineType(types: !172)
!172 = !{!23, !4, !80, !80}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !5, file: !6, line: 114, baseType: !166, size: 64, align: 64, offset: 2304)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !5, file: !6, line: 115, baseType: !175, size: 64, align: 64, offset: 2368)
!175 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !176, size: 64, align: 64)
!176 = !DISubroutineType(types: !177)
!177 = !{!23, !4, !30}
!178 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !5, file: !6, line: 117, baseType: !179, size: 64, align: 64, offset: 2432)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DISubroutineType(types: !181)
!181 = !{!38, !4, !43, !45}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !5, file: !6, line: 119, baseType: !166, size: 64, align: 64, offset: 2496)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !5, file: !6, line: 120, baseType: !166, size: 64, align: 64, offset: 2560)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !5, file: !6, line: 126, baseType: !95, size: 64, align: 64, offset: 2624)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !5, file: !6, line: 127, baseType: !186, size: 64, align: 64, offset: 2688)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !188)
!188 = !DISubroutineType(types: !189)
!189 = !{!80, !24, !123}
!190 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !5, file: !6, line: 128, baseType: !123, size: 64, align: 64, offset: 2752)
!191 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !192, size: 64, align: 64)
!192 = !DICompositeType(tag: DW_TAG_structure_type, name: "private_data", file: !1, line: 55, size: 128, align: 64, elements: !193)
!193 = !{!194, !195, !196, !197, !198, !199, !200, !201, !202, !203}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "compression_level", scope: !192, file: !1, line: 56, baseType: !23, size: 32, align: 32)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "header_written", scope: !192, file: !1, line: 57, baseType: !13, size: 1, align: 32, offset: 32)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "version_number", scope: !192, file: !1, line: 58, baseType: !13, size: 1, align: 32, offset: 33)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "block_independence", scope: !192, file: !1, line: 59, baseType: !13, size: 1, align: 32, offset: 34)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "block_checksum", scope: !192, file: !1, line: 60, baseType: !13, size: 1, align: 32, offset: 35)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "stream_size", scope: !192, file: !1, line: 61, baseType: !13, size: 1, align: 32, offset: 36)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "stream_checksum", scope: !192, file: !1, line: 62, baseType: !13, size: 1, align: 32, offset: 37)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dictionary", scope: !192, file: !1, line: 63, baseType: !13, size: 1, align: 32, offset: 38)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "block_maximum_size", scope: !192, file: !1, line: 64, baseType: !13, size: 3, align: 32, offset: 39)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "pdata", scope: !192, file: !1, line: 80, baseType: !204, size: 64, align: 64, offset: 64)
!204 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !205, size: 64, align: 64)
!205 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_program_data", file: !6, line: 146, flags: DIFlagFwdDecl)
!206 = !{!207, !208, !209, !210, !211, !212}
!207 = distinct !DISubprogram(name: "archive_write_add_filter_lz4", scope: !1, file: !1, line: 96, type: !21, isLocal: false, isDefinition: true, scopeLine: 97, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!208 = distinct !DISubprogram(name: "archive_filter_lz4_options", scope: !1, file: !1, line: 157, type: !145, isLocal: true, isDefinition: true, scopeLine: 159, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!209 = distinct !DISubprogram(name: "archive_filter_lz4_open", scope: !1, file: !1, line: 648, type: !149, isLocal: true, isDefinition: true, scopeLine: 649, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!210 = distinct !DISubprogram(name: "archive_filter_lz4_write", scope: !1, file: !1, line: 681, type: !153, isLocal: true, isDefinition: true, scopeLine: 683, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!211 = distinct !DISubprogram(name: "archive_filter_lz4_close", scope: !1, file: !1, line: 690, type: !149, isLocal: true, isDefinition: true, scopeLine: 691, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!212 = distinct !DISubprogram(name: "archive_filter_lz4_free", scope: !1, file: !1, line: 698, type: !149, isLocal: true, isDefinition: true, scopeLine: 699, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!213 = !{i32 2, !"Dwarf Version", i32 4}
!214 = !{i32 2, !"Debug Info Version", i32 3}
!215 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!216 = !DILocalVariable(name: "_a", arg: 1, scope: !207, file: !1, line: 96, type: !24)
!217 = !DIExpression()
!218 = !DILocation(line: 96, column: 46, scope: !207)
!219 = !DILocalVariable(name: "a", scope: !207, file: !1, line: 98, type: !4)
!220 = !DILocation(line: 98, column: 24, scope: !207)
!221 = !DILocation(line: 98, column: 52, scope: !207)
!222 = !DILocation(line: 98, column: 28, scope: !207)
!223 = !DILocalVariable(name: "f", scope: !207, file: !1, line: 99, type: !137)
!224 = !DILocation(line: 99, column: 31, scope: !207)
!225 = !DILocation(line: 99, column: 67, scope: !207)
!226 = !DILocation(line: 99, column: 35, scope: !207)
!227 = !DILocalVariable(name: "data", scope: !207, file: !1, line: 100, type: !191)
!228 = !DILocation(line: 100, column: 23, scope: !207)
!229 = !DILocation(line: 102, column: 2, scope: !207)
!230 = !DILocalVariable(name: "magic_test", scope: !231, file: !1, line: 102, type: !23)
!231 = distinct !DILexicalBlock(scope: !207, file: !1, line: 102, column: 2)
!232 = !DILocation(line: 102, column: 2, scope: !231)
!233 = !DILocation(line: 102, column: 2, scope: !234)
!234 = !DILexicalBlockFile(scope: !231, file: !1, discriminator: 1)
!235 = !DILocation(line: 102, column: 2, scope: !236)
!236 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 2)
!237 = distinct !DILexicalBlock(scope: !231, file: !1, line: 102, column: 2)
!238 = !DILocation(line: 102, column: 2, scope: !239)
!239 = !DILexicalBlockFile(scope: !231, file: !1, discriminator: 3)
!240 = !DILocation(line: 105, column: 9, scope: !207)
!241 = !DILocation(line: 105, column: 7, scope: !207)
!242 = !DILocation(line: 106, column: 6, scope: !243)
!243 = distinct !DILexicalBlock(scope: !207, file: !1, line: 106, column: 6)
!244 = !DILocation(line: 106, column: 11, scope: !243)
!245 = !DILocation(line: 106, column: 6, scope: !207)
!246 = !DILocation(line: 107, column: 22, scope: !247)
!247 = distinct !DILexicalBlock(scope: !243, file: !1, line: 106, column: 20)
!248 = !DILocation(line: 107, column: 25, scope: !247)
!249 = !DILocation(line: 107, column: 3, scope: !247)
!250 = !DILocation(line: 108, column: 3, scope: !247)
!251 = !DILocation(line: 114, column: 2, scope: !207)
!252 = !DILocation(line: 114, column: 8, scope: !207)
!253 = !DILocation(line: 114, column: 26, scope: !207)
!254 = !DILocation(line: 115, column: 2, scope: !207)
!255 = !DILocation(line: 115, column: 8, scope: !207)
!256 = !DILocation(line: 115, column: 23, scope: !207)
!257 = !DILocation(line: 116, column: 2, scope: !207)
!258 = !DILocation(line: 116, column: 8, scope: !207)
!259 = !DILocation(line: 116, column: 27, scope: !207)
!260 = !DILocation(line: 117, column: 2, scope: !207)
!261 = !DILocation(line: 117, column: 8, scope: !207)
!262 = !DILocation(line: 117, column: 23, scope: !207)
!263 = !DILocation(line: 118, column: 2, scope: !207)
!264 = !DILocation(line: 118, column: 8, scope: !207)
!265 = !DILocation(line: 118, column: 20, scope: !207)
!266 = !DILocation(line: 119, column: 2, scope: !207)
!267 = !DILocation(line: 119, column: 8, scope: !207)
!268 = !DILocation(line: 119, column: 24, scope: !207)
!269 = !DILocation(line: 120, column: 2, scope: !207)
!270 = !DILocation(line: 120, column: 8, scope: !207)
!271 = !DILocation(line: 120, column: 26, scope: !207)
!272 = !DILocation(line: 121, column: 2, scope: !207)
!273 = !DILocation(line: 121, column: 8, scope: !207)
!274 = !DILocation(line: 121, column: 27, scope: !207)
!275 = !DILocation(line: 126, column: 12, scope: !207)
!276 = !DILocation(line: 126, column: 2, scope: !207)
!277 = !DILocation(line: 126, column: 5, scope: !207)
!278 = !DILocation(line: 126, column: 10, scope: !207)
!279 = !DILocation(line: 127, column: 2, scope: !207)
!280 = !DILocation(line: 127, column: 5, scope: !207)
!281 = !DILocation(line: 127, column: 13, scope: !207)
!282 = !DILocation(line: 128, column: 2, scope: !207)
!283 = !DILocation(line: 128, column: 5, scope: !207)
!284 = !DILocation(line: 128, column: 11, scope: !207)
!285 = !DILocation(line: 129, column: 2, scope: !207)
!286 = !DILocation(line: 129, column: 5, scope: !207)
!287 = !DILocation(line: 129, column: 10, scope: !207)
!288 = !DILocation(line: 130, column: 2, scope: !207)
!289 = !DILocation(line: 130, column: 5, scope: !207)
!290 = !DILocation(line: 130, column: 10, scope: !207)
!291 = !DILocation(line: 131, column: 2, scope: !207)
!292 = !DILocation(line: 131, column: 5, scope: !207)
!293 = !DILocation(line: 131, column: 10, scope: !207)
!294 = !DILocation(line: 132, column: 2, scope: !207)
!295 = !DILocation(line: 132, column: 5, scope: !207)
!296 = !DILocation(line: 132, column: 10, scope: !207)
!297 = !DILocation(line: 140, column: 16, scope: !207)
!298 = !DILocation(line: 140, column: 2, scope: !207)
!299 = !DILocation(line: 140, column: 8, scope: !207)
!300 = !DILocation(line: 140, column: 14, scope: !207)
!301 = !DILocation(line: 141, column: 6, scope: !302)
!302 = distinct !DILexicalBlock(scope: !207, file: !1, line: 141, column: 6)
!303 = !DILocation(line: 141, column: 12, scope: !302)
!304 = !DILocation(line: 141, column: 18, scope: !302)
!305 = !DILocation(line: 141, column: 6, scope: !207)
!306 = !DILocation(line: 142, column: 8, scope: !307)
!307 = distinct !DILexicalBlock(scope: !302, file: !1, line: 141, column: 27)
!308 = !DILocation(line: 142, column: 3, scope: !307)
!309 = !DILocation(line: 143, column: 22, scope: !307)
!310 = !DILocation(line: 143, column: 25, scope: !307)
!311 = !DILocation(line: 143, column: 3, scope: !307)
!312 = !DILocation(line: 144, column: 3, scope: !307)
!313 = !DILocation(line: 146, column: 2, scope: !207)
!314 = !DILocation(line: 146, column: 8, scope: !207)
!315 = !DILocation(line: 146, column: 26, scope: !207)
!316 = !DILocation(line: 147, column: 21, scope: !207)
!317 = !DILocation(line: 147, column: 24, scope: !207)
!318 = !DILocation(line: 147, column: 2, scope: !207)
!319 = !DILocation(line: 149, column: 2, scope: !207)
!320 = !DILocation(line: 151, column: 1, scope: !207)
!321 = !DILocalVariable(name: "f", arg: 1, scope: !208, file: !1, line: 157, type: !137)
!322 = !DILocation(line: 157, column: 57, scope: !208)
!323 = !DILocalVariable(name: "key", arg: 2, scope: !208, file: !1, line: 158, type: !80)
!324 = !DILocation(line: 158, column: 17, scope: !208)
!325 = !DILocalVariable(name: "value", arg: 3, scope: !208, file: !1, line: 158, type: !80)
!326 = !DILocation(line: 158, column: 34, scope: !208)
!327 = !DILocalVariable(name: "data", scope: !208, file: !1, line: 160, type: !191)
!328 = !DILocation(line: 160, column: 23, scope: !208)
!329 = !DILocation(line: 160, column: 53, scope: !208)
!330 = !DILocation(line: 160, column: 56, scope: !208)
!331 = !DILocation(line: 160, column: 30, scope: !208)
!332 = !DILocation(line: 162, column: 13, scope: !333)
!333 = distinct !DILexicalBlock(scope: !208, file: !1, line: 162, column: 6)
!334 = !DILocation(line: 162, column: 6, scope: !333)
!335 = !DILocation(line: 162, column: 39, scope: !333)
!336 = !DILocation(line: 162, column: 6, scope: !208)
!337 = !DILocalVariable(name: "val", scope: !338, file: !1, line: 163, type: !23)
!338 = distinct !DILexicalBlock(scope: !333, file: !1, line: 162, column: 45)
!339 = !DILocation(line: 163, column: 7, scope: !338)
!340 = !DILocation(line: 164, column: 7, scope: !341)
!341 = distinct !DILexicalBlock(scope: !338, file: !1, line: 164, column: 7)
!342 = !DILocation(line: 164, column: 13, scope: !341)
!343 = !DILocation(line: 164, column: 21, scope: !341)
!344 = !DILocation(line: 164, column: 33, scope: !345)
!345 = !DILexicalBlockFile(scope: !341, file: !1, discriminator: 1)
!346 = !DILocation(line: 164, column: 42, scope: !345)
!347 = !DILocation(line: 164, column: 31, scope: !345)
!348 = !DILocation(line: 164, column: 49, scope: !345)
!349 = !DILocation(line: 164, column: 54, scope: !345)
!350 = !DILocation(line: 164, column: 57, scope: !351)
!351 = !DILexicalBlockFile(scope: !341, file: !1, discriminator: 2)
!352 = !DILocation(line: 164, column: 61, scope: !351)
!353 = !DILocation(line: 164, column: 67, scope: !351)
!354 = !DILocation(line: 165, column: 7, scope: !341)
!355 = !DILocation(line: 165, column: 16, scope: !341)
!356 = !DILocation(line: 164, column: 7, scope: !357)
!357 = !DILexicalBlockFile(scope: !338, file: !1, discriminator: 3)
!358 = !DILocation(line: 166, column: 4, scope: !341)
!359 = !DILocation(line: 169, column: 6, scope: !360)
!360 = distinct !DILexicalBlock(scope: !338, file: !1, line: 169, column: 6)
!361 = !DILocation(line: 169, column: 10, scope: !360)
!362 = !DILocation(line: 169, column: 6, scope: !338)
!363 = !DILocation(line: 171, column: 22, scope: !364)
!364 = distinct !DILexicalBlock(scope: !360, file: !1, line: 170, column: 3)
!365 = !DILocation(line: 171, column: 25, scope: !364)
!366 = !DILocation(line: 171, column: 4, scope: !364)
!367 = !DILocation(line: 173, column: 4, scope: !364)
!368 = !DILocation(line: 176, column: 29, scope: !338)
!369 = !DILocation(line: 176, column: 3, scope: !338)
!370 = !DILocation(line: 176, column: 9, scope: !338)
!371 = !DILocation(line: 176, column: 27, scope: !338)
!372 = !DILocation(line: 177, column: 3, scope: !338)
!373 = !DILocation(line: 179, column: 13, scope: !374)
!374 = distinct !DILexicalBlock(scope: !208, file: !1, line: 179, column: 6)
!375 = !DILocation(line: 179, column: 6, scope: !374)
!376 = !DILocation(line: 179, column: 37, scope: !374)
!377 = !DILocation(line: 179, column: 6, scope: !208)
!378 = !DILocation(line: 180, column: 27, scope: !379)
!379 = distinct !DILexicalBlock(scope: !374, file: !1, line: 179, column: 43)
!380 = !DILocation(line: 180, column: 33, scope: !379)
!381 = !DILocation(line: 180, column: 3, scope: !379)
!382 = !DILocation(line: 180, column: 9, scope: !379)
!383 = !DILocation(line: 180, column: 25, scope: !379)
!384 = !DILocation(line: 181, column: 3, scope: !379)
!385 = !DILocation(line: 183, column: 13, scope: !386)
!386 = distinct !DILexicalBlock(scope: !208, file: !1, line: 183, column: 6)
!387 = !DILocation(line: 183, column: 6, scope: !386)
!388 = !DILocation(line: 183, column: 36, scope: !386)
!389 = !DILocation(line: 183, column: 6, scope: !208)
!390 = !DILocation(line: 184, column: 26, scope: !391)
!391 = distinct !DILexicalBlock(scope: !386, file: !1, line: 183, column: 42)
!392 = !DILocation(line: 184, column: 32, scope: !391)
!393 = !DILocation(line: 184, column: 3, scope: !391)
!394 = !DILocation(line: 184, column: 9, scope: !391)
!395 = !DILocation(line: 184, column: 24, scope: !391)
!396 = !DILocation(line: 185, column: 3, scope: !391)
!397 = !DILocation(line: 187, column: 13, scope: !398)
!398 = distinct !DILexicalBlock(scope: !208, file: !1, line: 187, column: 6)
!399 = !DILocation(line: 187, column: 6, scope: !398)
!400 = !DILocation(line: 187, column: 32, scope: !398)
!401 = !DILocation(line: 187, column: 6, scope: !208)
!402 = !DILocation(line: 188, column: 7, scope: !403)
!403 = distinct !DILexicalBlock(scope: !404, file: !1, line: 188, column: 7)
!404 = distinct !DILexicalBlock(scope: !398, file: !1, line: 187, column: 38)
!405 = !DILocation(line: 188, column: 13, scope: !403)
!406 = !DILocation(line: 188, column: 21, scope: !403)
!407 = !DILocation(line: 188, column: 26, scope: !408)
!408 = !DILexicalBlockFile(scope: !403, file: !1, discriminator: 1)
!409 = !DILocation(line: 188, column: 35, scope: !408)
!410 = !DILocation(line: 188, column: 42, scope: !408)
!411 = !DILocation(line: 188, column: 45, scope: !412)
!412 = !DILexicalBlockFile(scope: !403, file: !1, discriminator: 2)
!413 = !DILocation(line: 188, column: 54, scope: !412)
!414 = !DILocation(line: 188, column: 62, scope: !412)
!415 = !DILocation(line: 189, column: 7, scope: !403)
!416 = !DILocation(line: 189, column: 16, scope: !403)
!417 = !DILocation(line: 188, column: 7, scope: !418)
!418 = !DILexicalBlockFile(scope: !404, file: !1, discriminator: 3)
!419 = !DILocation(line: 190, column: 4, scope: !403)
!420 = !DILocation(line: 191, column: 30, scope: !404)
!421 = !DILocation(line: 191, column: 39, scope: !404)
!422 = !DILocation(line: 191, column: 3, scope: !404)
!423 = !DILocation(line: 191, column: 9, scope: !404)
!424 = !DILocation(line: 191, column: 28, scope: !404)
!425 = !DILocation(line: 192, column: 3, scope: !404)
!426 = !DILocation(line: 194, column: 13, scope: !427)
!427 = distinct !DILexicalBlock(scope: !208, file: !1, line: 194, column: 6)
!428 = !DILocation(line: 194, column: 6, scope: !427)
!429 = !DILocation(line: 194, column: 38, scope: !427)
!430 = !DILocation(line: 194, column: 6, scope: !208)
!431 = !DILocation(line: 195, column: 30, scope: !432)
!432 = distinct !DILexicalBlock(scope: !427, file: !1, line: 194, column: 44)
!433 = !DILocation(line: 195, column: 36, scope: !432)
!434 = !DILocation(line: 195, column: 3, scope: !432)
!435 = !DILocation(line: 195, column: 9, scope: !432)
!436 = !DILocation(line: 195, column: 28, scope: !432)
!437 = !DILocation(line: 196, column: 3, scope: !432)
!438 = !DILocation(line: 202, column: 2, scope: !208)
!439 = !DILocation(line: 203, column: 1, scope: !208)
!440 = !DILocalVariable(name: "f", arg: 1, scope: !211, file: !1, line: 690, type: !137)
!441 = !DILocation(line: 690, column: 55, scope: !211)
!442 = !DILocalVariable(name: "data", scope: !211, file: !1, line: 692, type: !191)
!443 = !DILocation(line: 692, column: 23, scope: !211)
!444 = !DILocation(line: 692, column: 53, scope: !211)
!445 = !DILocation(line: 692, column: 56, scope: !211)
!446 = !DILocation(line: 692, column: 30, scope: !211)
!447 = !DILocation(line: 694, column: 39, scope: !211)
!448 = !DILocation(line: 694, column: 42, scope: !211)
!449 = !DILocation(line: 694, column: 48, scope: !211)
!450 = !DILocation(line: 694, column: 9, scope: !211)
!451 = !DILocation(line: 694, column: 2, scope: !211)
!452 = !DILocalVariable(name: "f", arg: 1, scope: !212, file: !1, line: 698, type: !137)
!453 = !DILocation(line: 698, column: 54, scope: !212)
!454 = !DILocalVariable(name: "data", scope: !212, file: !1, line: 700, type: !191)
!455 = !DILocation(line: 700, column: 23, scope: !212)
!456 = !DILocation(line: 700, column: 53, scope: !212)
!457 = !DILocation(line: 700, column: 56, scope: !212)
!458 = !DILocation(line: 700, column: 30, scope: !212)
!459 = !DILocation(line: 702, column: 31, scope: !212)
!460 = !DILocation(line: 702, column: 37, scope: !212)
!461 = !DILocation(line: 702, column: 2, scope: !212)
!462 = !DILocation(line: 703, column: 7, scope: !212)
!463 = !DILocation(line: 703, column: 2, scope: !212)
!464 = !DILocation(line: 704, column: 2, scope: !212)
!465 = !DILocalVariable(name: "f", arg: 1, scope: !209, file: !1, line: 648, type: !137)
!466 = !DILocation(line: 648, column: 54, scope: !209)
!467 = !DILocalVariable(name: "data", scope: !209, file: !1, line: 650, type: !191)
!468 = !DILocation(line: 650, column: 23, scope: !209)
!469 = !DILocation(line: 650, column: 53, scope: !209)
!470 = !DILocation(line: 650, column: 56, scope: !209)
!471 = !DILocation(line: 650, column: 30, scope: !209)
!472 = !DILocalVariable(name: "as", scope: !209, file: !1, line: 651, type: !91)
!473 = !DILocation(line: 651, column: 24, scope: !209)
!474 = !DILocalVariable(name: "r", scope: !209, file: !1, line: 652, type: !23)
!475 = !DILocation(line: 652, column: 6, scope: !209)
!476 = !DILocation(line: 654, column: 2, scope: !209)
!477 = !DILocation(line: 654, column: 2, scope: !478)
!478 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 1)
!479 = distinct !DILexicalBlock(scope: !209, file: !1, line: 654, column: 2)
!480 = !DILocation(line: 655, column: 2, scope: !209)
!481 = !DILocation(line: 658, column: 6, scope: !482)
!482 = distinct !DILexicalBlock(scope: !209, file: !1, line: 658, column: 6)
!483 = !DILocation(line: 658, column: 12, scope: !482)
!484 = !DILocation(line: 658, column: 30, scope: !482)
!485 = !DILocation(line: 658, column: 6, scope: !209)
!486 = !DILocation(line: 659, column: 3, scope: !487)
!487 = distinct !DILexicalBlock(scope: !482, file: !1, line: 658, column: 35)
!488 = !DILocation(line: 660, column: 37, scope: !487)
!489 = !DILocation(line: 660, column: 43, scope: !487)
!490 = !DILocation(line: 660, column: 35, scope: !487)
!491 = !DILocation(line: 660, column: 31, scope: !487)
!492 = !DILocation(line: 660, column: 3, scope: !487)
!493 = !DILocation(line: 661, column: 2, scope: !487)
!494 = !DILocation(line: 663, column: 2, scope: !209)
!495 = !DILocation(line: 664, column: 36, scope: !209)
!496 = !DILocation(line: 664, column: 42, scope: !209)
!497 = !DILocation(line: 664, column: 34, scope: !209)
!498 = !DILocation(line: 664, column: 30, scope: !209)
!499 = !DILocation(line: 664, column: 2, scope: !209)
!500 = !DILocation(line: 666, column: 6, scope: !501)
!501 = distinct !DILexicalBlock(scope: !209, file: !1, line: 666, column: 6)
!502 = !DILocation(line: 666, column: 12, scope: !501)
!503 = !DILocation(line: 666, column: 6, scope: !209)
!504 = !DILocation(line: 667, column: 3, scope: !501)
!505 = !DILocation(line: 668, column: 6, scope: !506)
!506 = distinct !DILexicalBlock(scope: !209, file: !1, line: 668, column: 6)
!507 = !DILocation(line: 668, column: 12, scope: !506)
!508 = !DILocation(line: 668, column: 28, scope: !506)
!509 = !DILocation(line: 668, column: 6, scope: !209)
!510 = !DILocation(line: 669, column: 3, scope: !506)
!511 = !DILocation(line: 670, column: 6, scope: !512)
!512 = distinct !DILexicalBlock(scope: !209, file: !1, line: 670, column: 6)
!513 = !DILocation(line: 670, column: 12, scope: !512)
!514 = !DILocation(line: 670, column: 31, scope: !512)
!515 = !DILocation(line: 670, column: 6, scope: !209)
!516 = !DILocation(line: 671, column: 3, scope: !512)
!517 = !DILocation(line: 673, column: 2, scope: !209)
!518 = !DILocation(line: 673, column: 5, scope: !209)
!519 = !DILocation(line: 673, column: 11, scope: !209)
!520 = !DILocation(line: 675, column: 35, scope: !209)
!521 = !DILocation(line: 675, column: 38, scope: !209)
!522 = !DILocation(line: 675, column: 44, scope: !209)
!523 = !DILocation(line: 675, column: 54, scope: !209)
!524 = !DILocation(line: 675, column: 6, scope: !209)
!525 = !DILocation(line: 675, column: 4, scope: !209)
!526 = !DILocation(line: 676, column: 2, scope: !209)
!527 = !DILocation(line: 677, column: 10, scope: !209)
!528 = !DILocation(line: 677, column: 2, scope: !209)
!529 = !DILocalVariable(name: "f", arg: 1, scope: !210, file: !1, line: 681, type: !137)
!530 = !DILocation(line: 681, column: 55, scope: !210)
!531 = !DILocalVariable(name: "buff", arg: 2, scope: !210, file: !1, line: 681, type: !43)
!532 = !DILocation(line: 681, column: 70, scope: !210)
!533 = !DILocalVariable(name: "length", arg: 3, scope: !210, file: !1, line: 682, type: !45)
!534 = !DILocation(line: 682, column: 12, scope: !210)
!535 = !DILocalVariable(name: "data", scope: !210, file: !1, line: 684, type: !191)
!536 = !DILocation(line: 684, column: 23, scope: !210)
!537 = !DILocation(line: 684, column: 53, scope: !210)
!538 = !DILocation(line: 684, column: 56, scope: !210)
!539 = !DILocation(line: 684, column: 30, scope: !210)
!540 = !DILocation(line: 686, column: 39, scope: !210)
!541 = !DILocation(line: 686, column: 42, scope: !210)
!542 = !DILocation(line: 686, column: 48, scope: !210)
!543 = !DILocation(line: 686, column: 55, scope: !210)
!544 = !DILocation(line: 686, column: 61, scope: !210)
!545 = !DILocation(line: 686, column: 9, scope: !210)
!546 = !DILocation(line: 686, column: 2, scope: !210)
