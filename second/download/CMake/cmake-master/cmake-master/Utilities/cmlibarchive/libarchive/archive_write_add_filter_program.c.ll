; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_program.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.private_data = type { %struct.archive_write_program_data*, %struct.archive_string, i8* }
%struct.archive_write_program_data = type { i32, i32, i32, i8*, i64, i64, i8* }

@archive_write_add_filter_program.prefix = internal global i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0), align 8
@.str = private unnamed_addr constant [10 x i8] c"Program: \00", align 1
@.str.1 = private unnamed_addr constant [33 x i8] c"archive_write_add_filter_program\00", align 1
@.str.2 = private unnamed_addr constant [41 x i8] c"Can't allocate memory for filter program\00", align 1
@.str.3 = private unnamed_addr constant [34 x i8] c"Can't allocate compression buffer\00", align 1
@.str.4 = private unnamed_addr constant [34 x i8] c"Can't launch external program: %s\00", align 1
@.str.5 = private unnamed_addr constant [27 x i8] c"Can't write to program: %s\00", align 1
@.str.6 = private unnamed_addr constant [31 x i8] c"Error reading from program: %s\00", align 1
@.str.7 = private unnamed_addr constant [26 x i8] c"Error closing program: %s\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_compression_program(%struct.archive* %a, i8* %cmd) #0 !dbg !38 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %cmd.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !183, metadata !184), !dbg !185
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !186, metadata !184), !dbg !187
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !188
  call void @__archive_write_filters_free(%struct.archive* %0), !dbg !189
  %1 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !190
  %2 = load i8*, i8** %cmd.addr, align 8, !dbg !191
  %call = call i32 @archive_write_add_filter_program(%struct.archive* %1, i8* %2), !dbg !192
  ret i32 %call, !dbg !193
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @__archive_write_filters_free(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_program(%struct.archive* %_a, i8* %cmd) #0 !dbg !129 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %cmd.addr = alloca i8*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !194, metadata !184), !dbg !195
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !196, metadata !184), !dbg !197
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !198, metadata !184), !dbg !199
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !200
  %call = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %0), !dbg !201
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !199
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !202, metadata !184), !dbg !203
  br label %do.body, !dbg !204

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !205, metadata !184), !dbg !207
  %1 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !208
  %call1 = call i32 @__archive_check_magic(%struct.archive* %1, i32 -1329217314, i32 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.1, i32 0, i32 0)), !dbg !208
  store i32 %call1, i32* %magic_test, align 4, !dbg !208
  %2 = load i32, i32* %magic_test, align 4, !dbg !208
  %cmp = icmp eq i32 %2, -30, !dbg !208
  br i1 %cmp, label %if.then, label %if.end, !dbg !208

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !210
  br label %return, !dbg !210

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !213

do.end:                                           ; preds = %if.end
  %call2 = call noalias i8* @calloc(i64 1, i64 40) #6, !dbg !215
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !216
  %data3 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 8, !dbg !217
  store i8* %call2, i8** %data3, align 8, !dbg !218
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !219
  %data4 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %4, i32 0, i32 8, !dbg !221
  %5 = load i8*, i8** %data4, align 8, !dbg !221
  %cmp5 = icmp eq i8* %5, null, !dbg !222
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !223

if.then6:                                         ; preds = %do.end
  br label %memerr, !dbg !224

if.end7:                                          ; preds = %do.end
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !225
  %data8 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 8, !dbg !226
  %7 = load i8*, i8** %data8, align 8, !dbg !226
  %8 = bitcast i8* %7 to %struct.private_data*, !dbg !227
  store %struct.private_data* %8, %struct.private_data** %data, align 8, !dbg !228
  %9 = load i8*, i8** %cmd.addr, align 8, !dbg !229
  %call9 = call noalias i8* @strdup(i8* %9) #6, !dbg !230
  %10 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !231
  %cmd10 = getelementptr inbounds %struct.private_data, %struct.private_data* %10, i32 0, i32 2, !dbg !232
  store i8* %call9, i8** %cmd10, align 8, !dbg !233
  %11 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !234
  %cmd11 = getelementptr inbounds %struct.private_data, %struct.private_data* %11, i32 0, i32 2, !dbg !236
  %12 = load i8*, i8** %cmd11, align 8, !dbg !236
  %cmp12 = icmp eq i8* %12, null, !dbg !237
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !238

if.then13:                                        ; preds = %if.end7
  br label %memerr, !dbg !239

if.end14:                                         ; preds = %if.end7
  %13 = load i8*, i8** %cmd.addr, align 8, !dbg !240
  %call15 = call %struct.archive_write_program_data* @__archive_write_program_allocate(i8* %13), !dbg !241
  %14 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !242
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 0, !dbg !243
  store %struct.archive_write_program_data* %call15, %struct.archive_write_program_data** %pdata, align 8, !dbg !244
  %15 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !245
  %pdata16 = getelementptr inbounds %struct.private_data, %struct.private_data* %15, i32 0, i32 0, !dbg !247
  %16 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata16, align 8, !dbg !247
  %cmp17 = icmp eq %struct.archive_write_program_data* %16, null, !dbg !248
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !249

if.then18:                                        ; preds = %if.end14
  br label %memerr, !dbg !250

if.end19:                                         ; preds = %if.end14
  %17 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !251
  %description = getelementptr inbounds %struct.private_data, %struct.private_data* %17, i32 0, i32 1, !dbg !253
  %18 = load i8*, i8** @archive_write_add_filter_program.prefix, align 8, !dbg !254
  %call20 = call i64 @strlen(i8* %18) #7, !dbg !255
  %19 = load i8*, i8** %cmd.addr, align 8, !dbg !256
  %call21 = call i64 @strlen(i8* %19) #7, !dbg !257
  %add = add i64 %call20, %call21, !dbg !259
  %add22 = add i64 %add, 1, !dbg !260
  %call23 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %description, i64 %add22), !dbg !261
  %cmp24 = icmp eq %struct.archive_string* %call23, null, !dbg !262
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !263

if.then25:                                        ; preds = %if.end19
  br label %memerr, !dbg !264

if.end26:                                         ; preds = %if.end19
  %20 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !265
  %description27 = getelementptr inbounds %struct.private_data, %struct.private_data* %20, i32 0, i32 1, !dbg !265
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %description27, i32 0, i32 1, !dbg !265
  store i64 0, i64* %length, align 8, !dbg !265
  %21 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !265
  %description28 = getelementptr inbounds %struct.private_data, %struct.private_data* %21, i32 0, i32 1, !dbg !265
  %22 = load i8*, i8** @archive_write_add_filter_program.prefix, align 8, !dbg !265
  %23 = load i8*, i8** @archive_write_add_filter_program.prefix, align 8, !dbg !265
  %cmp29 = icmp eq i8* %23, null, !dbg !265
  br i1 %cmp29, label %cond.true, label %cond.false, !dbg !265

cond.true:                                        ; preds = %if.end26
  br label %cond.end, !dbg !266

cond.false:                                       ; preds = %if.end26
  %24 = load i8*, i8** @archive_write_add_filter_program.prefix, align 8, !dbg !268
  %call30 = call i64 @strlen(i8* %24) #7, !dbg !268
  br label %cond.end, !dbg !268

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call30, %cond.false ], !dbg !270
  %call31 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %description28, i8* %22, i64 %cond), !dbg !270
  %25 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !272
  %description32 = getelementptr inbounds %struct.private_data, %struct.private_data* %25, i32 0, i32 1, !dbg !273
  %26 = load i8*, i8** %cmd.addr, align 8, !dbg !274
  %call33 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %description32, i8* %26), !dbg !275
  %27 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !276
  %description34 = getelementptr inbounds %struct.private_data, %struct.private_data* %27, i32 0, i32 1, !dbg !277
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %description34, i32 0, i32 0, !dbg !278
  %28 = load i8*, i8** %s, align 8, !dbg !278
  %29 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !279
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %29, i32 0, i32 9, !dbg !280
  store i8* %28, i8** %name, align 8, !dbg !281
  %30 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !282
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %30, i32 0, i32 10, !dbg !283
  store i32 4, i32* %code, align 8, !dbg !284
  %31 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !285
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %31, i32 0, i32 4, !dbg !286
  store i32 (%struct.archive_write_filter*)* @archive_compressor_program_open, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !287
  %32 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !288
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %32, i32 0, i32 5, !dbg !289
  store i32 (%struct.archive_write_filter*, i8*, i64)* @archive_compressor_program_write, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !290
  %33 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !291
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %33, i32 0, i32 6, !dbg !292
  store i32 (%struct.archive_write_filter*)* @archive_compressor_program_close, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !293
  %34 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !294
  %free = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %34, i32 0, i32 7, !dbg !295
  store i32 (%struct.archive_write_filter*)* @archive_compressor_program_free, i32 (%struct.archive_write_filter*)** %free, align 8, !dbg !296
  store i32 0, i32* %retval, align 4, !dbg !297
  br label %return, !dbg !297

memerr:                                           ; preds = %if.then25, %if.then18, %if.then13, %if.then6
  %35 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !298
  %call35 = call i32 @archive_compressor_program_free(%struct.archive_write_filter* %35), !dbg !299
  %36 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !300
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %36, i32 12, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.2, i32 0, i32 0)), !dbg !301
  store i32 -30, i32* %retval, align 4, !dbg !302
  br label %return, !dbg !302

return:                                           ; preds = %memerr, %cond.end, %if.then
  %37 = load i32, i32* %retval, align 4, !dbg !303
  ret i32 %37, !dbg !303
}

declare %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive*) #2

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #3

; Function Attrs: nounwind uwtable
define %struct.archive_write_program_data* @__archive_write_program_allocate(i8* %program) #0 !dbg !130 {
entry:
  %retval = alloca %struct.archive_write_program_data*, align 8
  %program.addr = alloca i8*, align 8
  %data = alloca %struct.archive_write_program_data*, align 8
  store i8* %program, i8** %program.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %program.addr, metadata !304, metadata !184), !dbg !305
  call void @llvm.dbg.declare(metadata %struct.archive_write_program_data** %data, metadata !306, metadata !184), !dbg !307
  %call = call noalias i8* @calloc(i64 1, i64 48) #6, !dbg !308
  %0 = bitcast i8* %call to %struct.archive_write_program_data*, !dbg !308
  store %struct.archive_write_program_data* %0, %struct.archive_write_program_data** %data, align 8, !dbg !309
  %1 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data, align 8, !dbg !310
  %cmp = icmp eq %struct.archive_write_program_data* %1, null, !dbg !312
  br i1 %cmp, label %if.then, label %if.end, !dbg !313

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data, align 8, !dbg !314
  store %struct.archive_write_program_data* %2, %struct.archive_write_program_data** %retval, align 8, !dbg !315
  br label %return, !dbg !315

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data, align 8, !dbg !316
  %child_stdin = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %3, i32 0, i32 1, !dbg !317
  store i32 -1, i32* %child_stdin, align 4, !dbg !318
  %4 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data, align 8, !dbg !319
  %child_stdout = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %4, i32 0, i32 2, !dbg !320
  store i32 -1, i32* %child_stdout, align 8, !dbg !321
  %5 = load i8*, i8** %program.addr, align 8, !dbg !322
  %call1 = call noalias i8* @strdup(i8* %5) #6, !dbg !323
  %6 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data, align 8, !dbg !324
  %program_name = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %6, i32 0, i32 6, !dbg !325
  store i8* %call1, i8** %program_name, align 8, !dbg !326
  %7 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data, align 8, !dbg !327
  store %struct.archive_write_program_data* %7, %struct.archive_write_program_data** %retval, align 8, !dbg !328
  br label %return, !dbg !328

return:                                           ; preds = %if.end, %if.then
  %8 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %retval, align 8, !dbg !329
  ret %struct.archive_write_program_data* %8, !dbg !329
}

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare %struct.archive_string* @archive_strcat(%struct.archive_string*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_program_open(%struct.archive_write_filter* %f) #0 !dbg !171 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !330, metadata !184), !dbg !331
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !332, metadata !184), !dbg !333
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !334
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !335
  %1 = load i8*, i8** %data1, align 8, !dbg !335
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !336
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !333
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !337
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !338
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 0, !dbg !339
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !339
  %6 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !340
  %cmd = getelementptr inbounds %struct.private_data, %struct.private_data* %6, i32 0, i32 2, !dbg !341
  %7 = load i8*, i8** %cmd, align 8, !dbg !341
  %call = call i32 @__archive_write_program_open(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5, i8* %7), !dbg !342
  ret i32 %call, !dbg !343
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_program_write(%struct.archive_write_filter* %f, i8* %buff, i64 %length) #0 !dbg !172 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !344, metadata !184), !dbg !345
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !346, metadata !184), !dbg !347
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !348, metadata !184), !dbg !349
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !350, metadata !184), !dbg !351
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !352
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !353
  %1 = load i8*, i8** %data1, align 8, !dbg !353
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !354
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !351
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !355
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !356
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 0, !dbg !357
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !357
  %6 = load i8*, i8** %buff.addr, align 8, !dbg !358
  %7 = load i64, i64* %length.addr, align 8, !dbg !359
  %call = call i32 @__archive_write_program_write(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5, i8* %6, i64 %7), !dbg !360
  ret i32 %call, !dbg !361
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_program_close(%struct.archive_write_filter* %f) #0 !dbg !173 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !362, metadata !184), !dbg !363
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !364, metadata !184), !dbg !365
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !366
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !367
  %1 = load i8*, i8** %data1, align 8, !dbg !367
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !368
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !365
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !369
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !370
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 0, !dbg !371
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !371
  %call = call i32 @__archive_write_program_close(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5), !dbg !372
  ret i32 %call, !dbg !373
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_program_free(%struct.archive_write_filter* %f) #0 !dbg !174 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !374, metadata !184), !dbg !375
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !376, metadata !184), !dbg !377
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !378
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !379
  %1 = load i8*, i8** %data1, align 8, !dbg !379
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !380
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !377
  %3 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !381
  %tobool = icmp ne %struct.private_data* %3, null, !dbg !381
  br i1 %tobool, label %if.then, label %if.end, !dbg !383

if.then:                                          ; preds = %entry
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !384
  %cmd = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 2, !dbg !386
  %5 = load i8*, i8** %cmd, align 8, !dbg !386
  call void @free(i8* %5) #6, !dbg !387
  %6 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !388
  %description = getelementptr inbounds %struct.private_data, %struct.private_data* %6, i32 0, i32 1, !dbg !389
  call void @archive_string_free(%struct.archive_string* %description), !dbg !390
  %7 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !391
  %pdata = getelementptr inbounds %struct.private_data, %struct.private_data* %7, i32 0, i32 0, !dbg !392
  %8 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !392
  %call = call i32 @__archive_write_program_free(%struct.archive_write_program_data* %8), !dbg !393
  %9 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !394
  %10 = bitcast %struct.private_data* %9 to i8*, !dbg !394
  call void @free(i8* %10) #6, !dbg !395
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !396
  %data2 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 8, !dbg !397
  store i8* null, i8** %data2, align 8, !dbg !398
  br label %if.end, !dbg !399

if.end:                                           ; preds = %if.then, %entry
  ret i32 0, !dbg !400
}

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define i32 @__archive_write_program_free(%struct.archive_write_program_data* %data) #0 !dbg !133 {
entry:
  %data.addr = alloca %struct.archive_write_program_data*, align 8
  store %struct.archive_write_program_data* %data, %struct.archive_write_program_data** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_program_data** %data.addr, metadata !401, metadata !184), !dbg !402
  %0 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !403
  %tobool = icmp ne %struct.archive_write_program_data* %0, null, !dbg !403
  br i1 %tobool, label %if.then, label %if.end, !dbg !405

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !406
  %program_name = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %1, i32 0, i32 6, !dbg !408
  %2 = load i8*, i8** %program_name, align 8, !dbg !408
  call void @free(i8* %2) #6, !dbg !409
  %3 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !410
  %child_buf = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %3, i32 0, i32 3, !dbg !411
  %4 = load i8*, i8** %child_buf, align 8, !dbg !411
  call void @free(i8* %4) #6, !dbg !412
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !413
  %6 = bitcast %struct.archive_write_program_data* %5 to i8*, !dbg !413
  call void @free(i8* %6) #6, !dbg !414
  br label %if.end, !dbg !415

if.end:                                           ; preds = %if.then, %entry
  ret i32 0, !dbg !416
}

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define i32 @__archive_write_program_open(%struct.archive_write_filter* %f, %struct.archive_write_program_data* %data, i8* %cmd) #0 !dbg !136 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data.addr = alloca %struct.archive_write_program_data*, align 8
  %cmd.addr = alloca i8*, align 8
  %child = alloca i32, align 4
  %ret = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !417, metadata !184), !dbg !418
  store %struct.archive_write_program_data* %data, %struct.archive_write_program_data** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_program_data** %data.addr, metadata !419, metadata !184), !dbg !420
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !421, metadata !184), !dbg !422
  call void @llvm.dbg.declare(metadata i32* %child, metadata !423, metadata !184), !dbg !424
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !425, metadata !184), !dbg !426
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !427
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 2, !dbg !428
  %1 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !428
  %call = call i32 @__archive_write_open_filter(%struct.archive_write_filter* %1), !dbg !429
  store i32 %call, i32* %ret, align 4, !dbg !430
  %2 = load i32, i32* %ret, align 4, !dbg !431
  %cmp = icmp ne i32 %2, 0, !dbg !433
  br i1 %cmp, label %if.then, label %if.end, !dbg !434

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %ret, align 4, !dbg !435
  store i32 %3, i32* %retval, align 4, !dbg !436
  br label %return, !dbg !436

if.end:                                           ; preds = %entry
  %4 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !437
  %child_buf = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %4, i32 0, i32 3, !dbg !439
  %5 = load i8*, i8** %child_buf, align 8, !dbg !439
  %cmp1 = icmp eq i8* %5, null, !dbg !440
  br i1 %cmp1, label %if.then2, label %if.end10, !dbg !441

if.then2:                                         ; preds = %if.end
  %6 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !442
  %child_buf_len = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %6, i32 0, i32 4, !dbg !444
  store i64 65536, i64* %child_buf_len, align 8, !dbg !445
  %7 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !446
  %child_buf_avail = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %7, i32 0, i32 5, !dbg !447
  store i64 0, i64* %child_buf_avail, align 8, !dbg !448
  %8 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !449
  %child_buf_len3 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %8, i32 0, i32 4, !dbg !450
  %9 = load i64, i64* %child_buf_len3, align 8, !dbg !450
  %call4 = call noalias i8* @malloc(i64 %9) #6, !dbg !451
  %10 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !452
  %child_buf5 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %10, i32 0, i32 3, !dbg !453
  store i8* %call4, i8** %child_buf5, align 8, !dbg !454
  %11 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !455
  %child_buf6 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %11, i32 0, i32 3, !dbg !457
  %12 = load i8*, i8** %child_buf6, align 8, !dbg !457
  %cmp7 = icmp eq i8* %12, null, !dbg !458
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !459

if.then8:                                         ; preds = %if.then2
  %13 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !460
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %13, i32 0, i32 1, !dbg !462
  %14 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !462
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %14, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.3, i32 0, i32 0)), !dbg !463
  store i32 -30, i32* %retval, align 4, !dbg !464
  br label %return, !dbg !464

if.end9:                                          ; preds = %if.then2
  br label %if.end10, !dbg !465

if.end10:                                         ; preds = %if.end9, %if.end
  %15 = load i8*, i8** %cmd.addr, align 8, !dbg !466
  %16 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !467
  %child_stdin = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %16, i32 0, i32 1, !dbg !468
  %17 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !469
  %child_stdout = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %17, i32 0, i32 2, !dbg !470
  %call11 = call i32 @__archive_create_child(i8* %15, i32* %child_stdin, i32* %child_stdout), !dbg !471
  store i32 %call11, i32* %child, align 4, !dbg !472
  %18 = load i32, i32* %child, align 4, !dbg !473
  %cmp12 = icmp eq i32 %18, -1, !dbg !475
  br i1 %cmp12, label %if.then13, label %if.end15, !dbg !476

if.then13:                                        ; preds = %if.end10
  %19 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !477
  %archive14 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %19, i32 0, i32 1, !dbg !479
  %20 = load %struct.archive*, %struct.archive** %archive14, align 8, !dbg !479
  %21 = load i8*, i8** %cmd.addr, align 8, !dbg !480
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %20, i32 22, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.4, i32 0, i32 0), i8* %21), !dbg !481
  store i32 -30, i32* %retval, align 4, !dbg !482
  br label %return, !dbg !482

if.end15:                                         ; preds = %if.end10
  %22 = load i32, i32* %child, align 4, !dbg !483
  %23 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !484
  %child16 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %23, i32 0, i32 0, !dbg !485
  store i32 %22, i32* %child16, align 8, !dbg !486
  store i32 0, i32* %retval, align 4, !dbg !487
  br label %return, !dbg !487

return:                                           ; preds = %if.end15, %if.then13, %if.then8, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !488
  ret i32 %24, !dbg !488
}

declare i32 @__archive_write_open_filter(%struct.archive_write_filter*) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

declare i32 @__archive_create_child(i8*, i32*, i32*) #2

; Function Attrs: nounwind uwtable
define i32 @__archive_write_program_write(%struct.archive_write_filter* %f, %struct.archive_write_program_data* %data, i8* %buff, i64 %length) #0 !dbg !165 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data.addr = alloca %struct.archive_write_program_data*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %ret = alloca i64, align 8
  %buf = alloca i8*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !489, metadata !184), !dbg !490
  store %struct.archive_write_program_data* %data, %struct.archive_write_program_data** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_program_data** %data.addr, metadata !491, metadata !184), !dbg !492
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !493, metadata !184), !dbg !494
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !495, metadata !184), !dbg !496
  call void @llvm.dbg.declare(metadata i64* %ret, metadata !497, metadata !184), !dbg !498
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !499, metadata !184), !dbg !500
  %0 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !501
  %child = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %0, i32 0, i32 0, !dbg !503
  %1 = load i32, i32* %child, align 8, !dbg !503
  %cmp = icmp eq i32 %1, 0, !dbg !504
  br i1 %cmp, label %if.then, label %if.end, !dbg !505

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !506
  br label %return, !dbg !506

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %buff.addr, align 8, !dbg !507
  store i8* %2, i8** %buf, align 8, !dbg !508
  br label %while.cond, !dbg !509

while.cond:                                       ; preds = %if.end5, %if.end
  %3 = load i64, i64* %length.addr, align 8, !dbg !510
  %cmp1 = icmp ugt i64 %3, 0, !dbg !512
  br i1 %cmp1, label %while.body, label %while.end, !dbg !513

while.body:                                       ; preds = %while.cond
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !514
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !516
  %6 = load i8*, i8** %buf, align 8, !dbg !517
  %7 = load i64, i64* %length.addr, align 8, !dbg !518
  %call = call i64 @child_write(%struct.archive_write_filter* %4, %struct.archive_write_program_data* %5, i8* %6, i64 %7), !dbg !519
  store i64 %call, i64* %ret, align 8, !dbg !520
  %8 = load i64, i64* %ret, align 8, !dbg !521
  %cmp2 = icmp eq i64 %8, -1, !dbg !523
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !524

lor.lhs.false:                                    ; preds = %while.body
  %9 = load i64, i64* %ret, align 8, !dbg !525
  %cmp3 = icmp eq i64 %9, 0, !dbg !527
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !528

if.then4:                                         ; preds = %lor.lhs.false, %while.body
  %10 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !529
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %10, i32 0, i32 1, !dbg !531
  %11 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !531
  %12 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !532
  %program_name = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %12, i32 0, i32 6, !dbg !533
  %13 = load i8*, i8** %program_name, align 8, !dbg !533
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %11, i32 5, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.5, i32 0, i32 0), i8* %13), !dbg !534
  store i32 -30, i32* %retval, align 4, !dbg !535
  br label %return, !dbg !535

if.end5:                                          ; preds = %lor.lhs.false
  %14 = load i64, i64* %ret, align 8, !dbg !536
  %15 = load i64, i64* %length.addr, align 8, !dbg !537
  %sub = sub i64 %15, %14, !dbg !537
  store i64 %sub, i64* %length.addr, align 8, !dbg !537
  %16 = load i64, i64* %ret, align 8, !dbg !538
  %17 = load i8*, i8** %buf, align 8, !dbg !539
  %add.ptr = getelementptr inbounds i8, i8* %17, i64 %16, !dbg !539
  store i8* %add.ptr, i8** %buf, align 8, !dbg !539
  br label %while.cond, !dbg !540

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !542
  br label %return, !dbg !542

return:                                           ; preds = %while.end, %if.then4, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !543
  ret i32 %18, !dbg !543
}

; Function Attrs: nounwind uwtable
define internal i64 @child_write(%struct.archive_write_filter* %f, %struct.archive_write_program_data* %data, i8* %buf, i64 %buf_len) #0 !dbg !175 {
entry:
  %retval = alloca i64, align 8
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data.addr = alloca %struct.archive_write_program_data*, align 8
  %buf.addr = alloca i8*, align 8
  %buf_len.addr = alloca i64, align 8
  %ret = alloca i64, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !544, metadata !184), !dbg !545
  store %struct.archive_write_program_data* %data, %struct.archive_write_program_data** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_program_data** %data.addr, metadata !546, metadata !184), !dbg !547
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !548, metadata !184), !dbg !549
  store i64 %buf_len, i64* %buf_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %buf_len.addr, metadata !550, metadata !184), !dbg !551
  call void @llvm.dbg.declare(metadata i64* %ret, metadata !552, metadata !184), !dbg !553
  %0 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !554
  %child_stdin = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %0, i32 0, i32 1, !dbg !556
  %1 = load i32, i32* %child_stdin, align 4, !dbg !556
  %cmp = icmp eq i32 %1, -1, !dbg !557
  br i1 %cmp, label %if.then, label %if.end, !dbg !558

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !559
  br label %return, !dbg !559

if.end:                                           ; preds = %entry
  %2 = load i64, i64* %buf_len.addr, align 8, !dbg !560
  %cmp1 = icmp eq i64 %2, 0, !dbg !562
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !563

if.then2:                                         ; preds = %if.end
  store i64 -1, i64* %retval, align 8, !dbg !564
  br label %return, !dbg !564

if.end3:                                          ; preds = %if.end
  br label %for.cond, !dbg !565

for.cond:                                         ; preds = %if.end72, %if.then58, %if.then47, %if.then25, %if.end3
  br label %do.body, !dbg !566

do.body:                                          ; preds = %land.end, %for.cond
  %3 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !570
  %child_stdin4 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %3, i32 0, i32 1, !dbg !572
  %4 = load i32, i32* %child_stdin4, align 4, !dbg !572
  %5 = load i8*, i8** %buf.addr, align 8, !dbg !573
  %6 = load i64, i64* %buf_len.addr, align 8, !dbg !574
  %call = call i64 @write(i32 %4, i8* %5, i64 %6), !dbg !575
  store i64 %call, i64* %ret, align 8, !dbg !576
  br label %do.cond, !dbg !577

do.cond:                                          ; preds = %do.body
  %7 = load i64, i64* %ret, align 8, !dbg !578
  %cmp5 = icmp eq i64 %7, -1, !dbg !580
  br i1 %cmp5, label %land.rhs, label %land.end, !dbg !581

land.rhs:                                         ; preds = %do.cond
  %call6 = call i32* @__errno_location() #1, !dbg !582
  %8 = load i32, i32* %call6, align 4, !dbg !582
  %cmp7 = icmp eq i32 %8, 4, !dbg !584
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %9 = phi i1 [ false, %do.cond ], [ %cmp7, %land.rhs ]
  br i1 %9, label %do.body, label %do.end, !dbg !585

do.end:                                           ; preds = %land.end
  %10 = load i64, i64* %ret, align 8, !dbg !587
  %cmp8 = icmp sgt i64 %10, 0, !dbg !589
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !590

if.then9:                                         ; preds = %do.end
  %11 = load i64, i64* %ret, align 8, !dbg !591
  store i64 %11, i64* %retval, align 8, !dbg !592
  br label %return, !dbg !592

if.end10:                                         ; preds = %do.end
  %12 = load i64, i64* %ret, align 8, !dbg !593
  %cmp11 = icmp eq i64 %12, 0, !dbg !595
  br i1 %cmp11, label %if.then12, label %if.end17, !dbg !596

if.then12:                                        ; preds = %if.end10
  %13 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !597
  %child_stdin13 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %13, i32 0, i32 1, !dbg !599
  %14 = load i32, i32* %child_stdin13, align 4, !dbg !599
  %call14 = call i32 @close(i32 %14), !dbg !600
  %15 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !601
  %child_stdin15 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %15, i32 0, i32 1, !dbg !602
  store i32 -1, i32* %child_stdin15, align 4, !dbg !603
  %16 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !604
  %child_stdout = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %16, i32 0, i32 2, !dbg !605
  %17 = load i32, i32* %child_stdout, align 8, !dbg !605
  %call16 = call i32 (i32, i32, ...) @fcntl(i32 %17, i32 4, i32 0), !dbg !606
  store i64 0, i64* %retval, align 8, !dbg !607
  br label %return, !dbg !607

if.end17:                                         ; preds = %if.end10
  %18 = load i64, i64* %ret, align 8, !dbg !608
  %cmp18 = icmp eq i64 %18, -1, !dbg !610
  br i1 %cmp18, label %land.lhs.true, label %if.end22, !dbg !611

land.lhs.true:                                    ; preds = %if.end17
  %call19 = call i32* @__errno_location() #1, !dbg !612
  %19 = load i32, i32* %call19, align 4, !dbg !612
  %cmp20 = icmp ne i32 %19, 11, !dbg !614
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !615

if.then21:                                        ; preds = %land.lhs.true
  store i64 -1, i64* %retval, align 8, !dbg !616
  br label %return, !dbg !616

if.end22:                                         ; preds = %land.lhs.true, %if.end17
  %20 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !617
  %child_stdout23 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %20, i32 0, i32 2, !dbg !619
  %21 = load i32, i32* %child_stdout23, align 8, !dbg !619
  %cmp24 = icmp eq i32 %21, -1, !dbg !620
  br i1 %cmp24, label %if.then25, label %if.end30, !dbg !621

if.then25:                                        ; preds = %if.end22
  %22 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !622
  %child_stdin26 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %22, i32 0, i32 1, !dbg !624
  %23 = load i32, i32* %child_stdin26, align 4, !dbg !624
  %call27 = call i32 (i32, i32, ...) @fcntl(i32 %23, i32 4, i32 0), !dbg !625
  %24 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !626
  %child_stdin28 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %24, i32 0, i32 1, !dbg !627
  %25 = load i32, i32* %child_stdin28, align 4, !dbg !627
  %26 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !628
  %child_stdout29 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %26, i32 0, i32 2, !dbg !629
  %27 = load i32, i32* %child_stdout29, align 8, !dbg !629
  call void @__archive_check_child(i32 %25, i32 %27), !dbg !630
  br label %for.cond, !dbg !631

if.end30:                                         ; preds = %if.end22
  br label %do.body31, !dbg !632

do.body31:                                        ; preds = %land.end40, %if.end30
  %28 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !633
  %child_stdout32 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %28, i32 0, i32 2, !dbg !635
  %29 = load i32, i32* %child_stdout32, align 8, !dbg !635
  %30 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !636
  %child_buf = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %30, i32 0, i32 3, !dbg !637
  %31 = load i8*, i8** %child_buf, align 8, !dbg !637
  %32 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !638
  %child_buf_avail = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %32, i32 0, i32 5, !dbg !639
  %33 = load i64, i64* %child_buf_avail, align 8, !dbg !639
  %add.ptr = getelementptr inbounds i8, i8* %31, i64 %33, !dbg !640
  %34 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !641
  %child_buf_len = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %34, i32 0, i32 4, !dbg !642
  %35 = load i64, i64* %child_buf_len, align 8, !dbg !642
  %36 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !643
  %child_buf_avail33 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %36, i32 0, i32 5, !dbg !644
  %37 = load i64, i64* %child_buf_avail33, align 8, !dbg !644
  %sub = sub i64 %35, %37, !dbg !645
  %call34 = call i64 @read(i32 %29, i8* %add.ptr, i64 %sub), !dbg !646
  store i64 %call34, i64* %ret, align 8, !dbg !647
  br label %do.cond35, !dbg !648

do.cond35:                                        ; preds = %do.body31
  %38 = load i64, i64* %ret, align 8, !dbg !649
  %cmp36 = icmp eq i64 %38, -1, !dbg !650
  br i1 %cmp36, label %land.rhs37, label %land.end40, !dbg !651

land.rhs37:                                       ; preds = %do.cond35
  %call38 = call i32* @__errno_location() #1, !dbg !652
  %39 = load i32, i32* %call38, align 4, !dbg !652
  %cmp39 = icmp eq i32 %39, 4, !dbg !653
  br label %land.end40

land.end40:                                       ; preds = %land.rhs37, %do.cond35
  %40 = phi i1 [ false, %do.cond35 ], [ %cmp39, %land.rhs37 ]
  br i1 %40, label %do.body31, label %do.end41, !dbg !654

do.end41:                                         ; preds = %land.end40
  %41 = load i64, i64* %ret, align 8, !dbg !656
  %cmp42 = icmp eq i64 %41, 0, !dbg !658
  br i1 %cmp42, label %if.then47, label %lor.lhs.false, !dbg !659

lor.lhs.false:                                    ; preds = %do.end41
  %42 = load i64, i64* %ret, align 8, !dbg !660
  %cmp43 = icmp eq i64 %42, -1, !dbg !662
  br i1 %cmp43, label %land.lhs.true44, label %if.end53, !dbg !663

land.lhs.true44:                                  ; preds = %lor.lhs.false
  %call45 = call i32* @__errno_location() #1, !dbg !664
  %43 = load i32, i32* %call45, align 4, !dbg !664
  %cmp46 = icmp eq i32 %43, 32, !dbg !666
  br i1 %cmp46, label %if.then47, label %if.end53, !dbg !667

if.then47:                                        ; preds = %land.lhs.true44, %do.end41
  %44 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !668
  %child_stdout48 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %44, i32 0, i32 2, !dbg !670
  %45 = load i32, i32* %child_stdout48, align 8, !dbg !670
  %call49 = call i32 @close(i32 %45), !dbg !671
  %46 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !672
  %child_stdout50 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %46, i32 0, i32 2, !dbg !673
  store i32 -1, i32* %child_stdout50, align 8, !dbg !674
  %47 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !675
  %child_stdin51 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %47, i32 0, i32 1, !dbg !676
  %48 = load i32, i32* %child_stdin51, align 4, !dbg !676
  %call52 = call i32 (i32, i32, ...) @fcntl(i32 %48, i32 4, i32 0), !dbg !677
  br label %for.cond, !dbg !678

if.end53:                                         ; preds = %land.lhs.true44, %lor.lhs.false
  %49 = load i64, i64* %ret, align 8, !dbg !679
  %cmp54 = icmp eq i64 %49, -1, !dbg !681
  br i1 %cmp54, label %land.lhs.true55, label %if.end61, !dbg !682

land.lhs.true55:                                  ; preds = %if.end53
  %call56 = call i32* @__errno_location() #1, !dbg !683
  %50 = load i32, i32* %call56, align 4, !dbg !683
  %cmp57 = icmp eq i32 %50, 11, !dbg !685
  br i1 %cmp57, label %if.then58, label %if.end61, !dbg !686

if.then58:                                        ; preds = %land.lhs.true55
  %51 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !687
  %child_stdin59 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %51, i32 0, i32 1, !dbg !689
  %52 = load i32, i32* %child_stdin59, align 4, !dbg !689
  %53 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !690
  %child_stdout60 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %53, i32 0, i32 2, !dbg !691
  %54 = load i32, i32* %child_stdout60, align 8, !dbg !691
  call void @__archive_check_child(i32 %52, i32 %54), !dbg !692
  br label %for.cond, !dbg !693

if.end61:                                         ; preds = %land.lhs.true55, %if.end53
  %55 = load i64, i64* %ret, align 8, !dbg !694
  %cmp62 = icmp eq i64 %55, -1, !dbg !696
  br i1 %cmp62, label %if.then63, label %if.end64, !dbg !697

if.then63:                                        ; preds = %if.end61
  store i64 -1, i64* %retval, align 8, !dbg !698
  br label %return, !dbg !698

if.end64:                                         ; preds = %if.end61
  %56 = load i64, i64* %ret, align 8, !dbg !699
  %57 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !700
  %child_buf_avail65 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %57, i32 0, i32 5, !dbg !701
  %58 = load i64, i64* %child_buf_avail65, align 8, !dbg !702
  %add = add i64 %58, %56, !dbg !702
  store i64 %add, i64* %child_buf_avail65, align 8, !dbg !702
  %59 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !703
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %59, i32 0, i32 2, !dbg !704
  %60 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !704
  %61 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !705
  %child_buf66 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %61, i32 0, i32 3, !dbg !706
  %62 = load i8*, i8** %child_buf66, align 8, !dbg !706
  %63 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !707
  %child_buf_avail67 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %63, i32 0, i32 5, !dbg !708
  %64 = load i64, i64* %child_buf_avail67, align 8, !dbg !708
  %call68 = call i32 @__archive_write_filter(%struct.archive_write_filter* %60, i8* %62, i64 %64), !dbg !709
  %conv = sext i32 %call68 to i64, !dbg !709
  store i64 %conv, i64* %ret, align 8, !dbg !710
  %65 = load i64, i64* %ret, align 8, !dbg !711
  %cmp69 = icmp ne i64 %65, 0, !dbg !713
  br i1 %cmp69, label %if.then71, label %if.end72, !dbg !714

if.then71:                                        ; preds = %if.end64
  store i64 -1, i64* %retval, align 8, !dbg !715
  br label %return, !dbg !715

if.end72:                                         ; preds = %if.end64
  %66 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !716
  %child_buf_avail73 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %66, i32 0, i32 5, !dbg !717
  store i64 0, i64* %child_buf_avail73, align 8, !dbg !718
  br label %for.cond, !dbg !719

return:                                           ; preds = %if.then71, %if.then63, %if.then21, %if.then12, %if.then9, %if.then2, %if.then
  %67 = load i64, i64* %retval, align 8, !dbg !721
  ret i64 %67, !dbg !721
}

; Function Attrs: nounwind uwtable
define i32 @__archive_write_program_close(%struct.archive_write_filter* %f, %struct.archive_write_program_data* %data) #0 !dbg !168 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data.addr = alloca %struct.archive_write_program_data*, align 8
  %ret = alloca i32, align 4
  %r1 = alloca i32, align 4
  %status = alloca i32, align 4
  %bytes_read = alloca i64, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !722, metadata !184), !dbg !723
  store %struct.archive_write_program_data* %data, %struct.archive_write_program_data** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_program_data** %data.addr, metadata !724, metadata !184), !dbg !725
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !726, metadata !184), !dbg !727
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !728, metadata !184), !dbg !729
  call void @llvm.dbg.declare(metadata i32* %status, metadata !730, metadata !184), !dbg !731
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !732, metadata !184), !dbg !733
  %0 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !734
  %child = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %0, i32 0, i32 0, !dbg !736
  %1 = load i32, i32* %child, align 8, !dbg !736
  %cmp = icmp eq i32 %1, 0, !dbg !737
  br i1 %cmp, label %if.then, label %if.end, !dbg !738

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !739
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %2, i32 0, i32 2, !dbg !740
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !740
  %call = call i32 @__archive_write_close_filter(%struct.archive_write_filter* %3), !dbg !741
  store i32 %call, i32* %retval, align 4, !dbg !742
  br label %return, !dbg !742

if.end:                                           ; preds = %entry
  store i32 0, i32* %ret, align 4, !dbg !743
  %4 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !744
  %child_stdin = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %4, i32 0, i32 1, !dbg !745
  %5 = load i32, i32* %child_stdin, align 4, !dbg !745
  %call1 = call i32 @close(i32 %5), !dbg !746
  %6 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !747
  %child_stdin2 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %6, i32 0, i32 1, !dbg !748
  store i32 -1, i32* %child_stdin2, align 4, !dbg !749
  %7 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !750
  %child_stdout = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %7, i32 0, i32 2, !dbg !751
  %8 = load i32, i32* %child_stdout, align 8, !dbg !751
  %call3 = call i32 (i32, i32, ...) @fcntl(i32 %8, i32 4, i32 0), !dbg !752
  br label %for.cond, !dbg !753

for.cond:                                         ; preds = %if.end27, %if.end
  br label %do.body, !dbg !754

do.body:                                          ; preds = %land.end, %for.cond
  %9 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !758
  %child_stdout4 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %9, i32 0, i32 2, !dbg !760
  %10 = load i32, i32* %child_stdout4, align 8, !dbg !760
  %11 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !761
  %child_buf = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %11, i32 0, i32 3, !dbg !762
  %12 = load i8*, i8** %child_buf, align 8, !dbg !762
  %13 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !763
  %child_buf_avail = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %13, i32 0, i32 5, !dbg !764
  %14 = load i64, i64* %child_buf_avail, align 8, !dbg !764
  %add.ptr = getelementptr inbounds i8, i8* %12, i64 %14, !dbg !765
  %15 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !766
  %child_buf_len = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %15, i32 0, i32 4, !dbg !767
  %16 = load i64, i64* %child_buf_len, align 8, !dbg !767
  %17 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !768
  %child_buf_avail5 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %17, i32 0, i32 5, !dbg !769
  %18 = load i64, i64* %child_buf_avail5, align 8, !dbg !769
  %sub = sub i64 %16, %18, !dbg !770
  %call6 = call i64 @read(i32 %10, i8* %add.ptr, i64 %sub), !dbg !771
  store i64 %call6, i64* %bytes_read, align 8, !dbg !772
  br label %do.cond, !dbg !773

do.cond:                                          ; preds = %do.body
  %19 = load i64, i64* %bytes_read, align 8, !dbg !774
  %cmp7 = icmp eq i64 %19, -1, !dbg !776
  br i1 %cmp7, label %land.rhs, label %land.end, !dbg !777

land.rhs:                                         ; preds = %do.cond
  %call8 = call i32* @__errno_location() #1, !dbg !778
  %20 = load i32, i32* %call8, align 4, !dbg !778
  %cmp9 = icmp eq i32 %20, 4, !dbg !780
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %21 = phi i1 [ false, %do.cond ], [ %cmp9, %land.rhs ]
  br i1 %21, label %do.body, label %do.end, !dbg !781

do.end:                                           ; preds = %land.end
  %22 = load i64, i64* %bytes_read, align 8, !dbg !783
  %cmp10 = icmp eq i64 %22, 0, !dbg !785
  br i1 %cmp10, label %if.then14, label %lor.lhs.false, !dbg !786

lor.lhs.false:                                    ; preds = %do.end
  %23 = load i64, i64* %bytes_read, align 8, !dbg !787
  %cmp11 = icmp eq i64 %23, -1, !dbg !789
  br i1 %cmp11, label %land.lhs.true, label %if.end15, !dbg !790

land.lhs.true:                                    ; preds = %lor.lhs.false
  %call12 = call i32* @__errno_location() #1, !dbg !791
  %24 = load i32, i32* %call12, align 4, !dbg !791
  %cmp13 = icmp eq i32 %24, 32, !dbg !793
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !794

if.then14:                                        ; preds = %land.lhs.true, %do.end
  br label %for.end, !dbg !795

if.end15:                                         ; preds = %land.lhs.true, %lor.lhs.false
  %25 = load i64, i64* %bytes_read, align 8, !dbg !796
  %cmp16 = icmp eq i64 %25, -1, !dbg !798
  br i1 %cmp16, label %if.then17, label %if.end19, !dbg !799

if.then17:                                        ; preds = %if.end15
  %26 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !800
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %26, i32 0, i32 1, !dbg !802
  %27 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !802
  %call18 = call i32* @__errno_location() #1, !dbg !803
  %28 = load i32, i32* %call18, align 4, !dbg !803
  %29 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !804
  %program_name = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %29, i32 0, i32 6, !dbg !805
  %30 = load i8*, i8** %program_name, align 8, !dbg !805
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %27, i32 %28, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.6, i32 0, i32 0), i8* %30), !dbg !806
  store i32 -30, i32* %ret, align 4, !dbg !808
  br label %cleanup, !dbg !809

if.end19:                                         ; preds = %if.end15
  %31 = load i64, i64* %bytes_read, align 8, !dbg !810
  %32 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !811
  %child_buf_avail20 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %32, i32 0, i32 5, !dbg !812
  %33 = load i64, i64* %child_buf_avail20, align 8, !dbg !813
  %add = add i64 %33, %31, !dbg !813
  store i64 %add, i64* %child_buf_avail20, align 8, !dbg !813
  %34 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !814
  %next_filter21 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %34, i32 0, i32 2, !dbg !815
  %35 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter21, align 8, !dbg !815
  %36 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !816
  %child_buf22 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %36, i32 0, i32 3, !dbg !817
  %37 = load i8*, i8** %child_buf22, align 8, !dbg !817
  %38 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !818
  %child_buf_avail23 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %38, i32 0, i32 5, !dbg !819
  %39 = load i64, i64* %child_buf_avail23, align 8, !dbg !819
  %call24 = call i32 @__archive_write_filter(%struct.archive_write_filter* %35, i8* %37, i64 %39), !dbg !820
  store i32 %call24, i32* %ret, align 4, !dbg !821
  %40 = load i32, i32* %ret, align 4, !dbg !822
  %cmp25 = icmp ne i32 %40, 0, !dbg !824
  br i1 %cmp25, label %if.then26, label %if.end27, !dbg !825

if.then26:                                        ; preds = %if.end19
  store i32 -30, i32* %ret, align 4, !dbg !826
  br label %cleanup, !dbg !828

if.end27:                                         ; preds = %if.end19
  %41 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !829
  %child_buf_avail28 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %41, i32 0, i32 5, !dbg !830
  store i64 0, i64* %child_buf_avail28, align 8, !dbg !831
  br label %for.cond, !dbg !832

for.end:                                          ; preds = %if.then14
  br label %cleanup, !dbg !834

cleanup:                                          ; preds = %for.end, %if.then26, %if.then17
  %42 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !835
  %child_stdin29 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %42, i32 0, i32 1, !dbg !837
  %43 = load i32, i32* %child_stdin29, align 4, !dbg !837
  %cmp30 = icmp ne i32 %43, -1, !dbg !838
  br i1 %cmp30, label %if.then31, label %if.end34, !dbg !839

if.then31:                                        ; preds = %cleanup
  %44 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !840
  %child_stdin32 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %44, i32 0, i32 1, !dbg !841
  %45 = load i32, i32* %child_stdin32, align 4, !dbg !841
  %call33 = call i32 @close(i32 %45), !dbg !842
  br label %if.end34, !dbg !842

if.end34:                                         ; preds = %if.then31, %cleanup
  %46 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !843
  %child_stdout35 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %46, i32 0, i32 2, !dbg !845
  %47 = load i32, i32* %child_stdout35, align 8, !dbg !845
  %cmp36 = icmp ne i32 %47, -1, !dbg !846
  br i1 %cmp36, label %if.then37, label %if.end40, !dbg !847

if.then37:                                        ; preds = %if.end34
  %48 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !848
  %child_stdout38 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %48, i32 0, i32 2, !dbg !849
  %49 = load i32, i32* %child_stdout38, align 8, !dbg !849
  %call39 = call i32 @close(i32 %49), !dbg !850
  br label %if.end40, !dbg !850

if.end40:                                         ; preds = %if.then37, %if.end34
  br label %while.cond, !dbg !851

while.cond:                                       ; preds = %while.body, %if.end40
  %50 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !852
  %child41 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %50, i32 0, i32 0, !dbg !854
  %51 = load i32, i32* %child41, align 8, !dbg !854
  %call42 = call i32 @waitpid(i32 %51, i32* %status, i32 0), !dbg !855
  %cmp43 = icmp eq i32 %call42, -1, !dbg !856
  br i1 %cmp43, label %land.rhs44, label %land.end47, !dbg !857

land.rhs44:                                       ; preds = %while.cond
  %call45 = call i32* @__errno_location() #1, !dbg !858
  %52 = load i32, i32* %call45, align 4, !dbg !858
  %cmp46 = icmp eq i32 %52, 4, !dbg !860
  br label %land.end47

land.end47:                                       ; preds = %land.rhs44, %while.cond
  %53 = phi i1 [ false, %while.cond ], [ %cmp46, %land.rhs44 ]
  br i1 %53, label %while.body, label %while.end, !dbg !861

while.body:                                       ; preds = %land.end47
  br label %while.cond, !dbg !863

while.end:                                        ; preds = %land.end47
  %54 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !864
  %child48 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %54, i32 0, i32 0, !dbg !865
  store i32 0, i32* %child48, align 8, !dbg !866
  %55 = load i32, i32* %status, align 4, !dbg !867
  %cmp49 = icmp ne i32 %55, 0, !dbg !869
  br i1 %cmp49, label %if.then50, label %if.end53, !dbg !870

if.then50:                                        ; preds = %while.end
  %56 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !871
  %archive51 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %56, i32 0, i32 1, !dbg !873
  %57 = load %struct.archive*, %struct.archive** %archive51, align 8, !dbg !873
  %58 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %data.addr, align 8, !dbg !874
  %program_name52 = getelementptr inbounds %struct.archive_write_program_data, %struct.archive_write_program_data* %58, i32 0, i32 6, !dbg !875
  %59 = load i8*, i8** %program_name52, align 8, !dbg !875
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %57, i32 5, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.7, i32 0, i32 0), i8* %59), !dbg !876
  store i32 -30, i32* %ret, align 4, !dbg !877
  br label %if.end53, !dbg !878

if.end53:                                         ; preds = %if.then50, %while.end
  %60 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !879
  %next_filter54 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %60, i32 0, i32 2, !dbg !880
  %61 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter54, align 8, !dbg !880
  %call55 = call i32 @__archive_write_close_filter(%struct.archive_write_filter* %61), !dbg !881
  store i32 %call55, i32* %r1, align 4, !dbg !882
  %62 = load i32, i32* %r1, align 4, !dbg !883
  %63 = load i32, i32* %ret, align 4, !dbg !884
  %cmp56 = icmp slt i32 %62, %63, !dbg !885
  br i1 %cmp56, label %cond.true, label %cond.false, !dbg !883

cond.true:                                        ; preds = %if.end53
  %64 = load i32, i32* %r1, align 4, !dbg !886
  br label %cond.end, !dbg !887

cond.false:                                       ; preds = %if.end53
  %65 = load i32, i32* %ret, align 4, !dbg !888
  br label %cond.end, !dbg !889

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %64, %cond.true ], [ %65, %cond.false ], !dbg !890
  store i32 %cond, i32* %retval, align 4, !dbg !891
  br label %return, !dbg !891

return:                                           ; preds = %cond.end, %if.then
  %66 = load i32, i32* %retval, align 4, !dbg !892
  ret i32 %66, !dbg !892
}

declare i32 @__archive_write_close_filter(%struct.archive_write_filter*) #2

declare i32 @close(i32) #2

declare i32 @fcntl(i32, i32, ...) #2

declare i64 @read(i32, i8*, i64) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i32 @__archive_write_filter(%struct.archive_write_filter*, i8*, i64) #2

declare i32 @waitpid(i32, i32*, i32) #2

declare void @archive_string_free(%struct.archive_string*) #2

declare i64 @write(i32, i8*, i64) #2

declare void @__archive_check_child(i32, i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!180, !181}
!llvm.ident = !{!182}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !37, globals: !178)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_program.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "private_data", file: !1, line: 74, size: 320, align: 64, elements: !7)
!7 = !{!8, !29, !36}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "pdata", scope: !6, file: !1, line: 75, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_program_data", file: !1, line: 61, size: 384, align: 64, elements: !11)
!11 = !{!12, !18, !19, !20, !23, !27, !28}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "child", scope: !10, file: !1, line: 65, baseType: !13, size: 32, align: 32)
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !14, line: 61, baseType: !15)
!14 = !DIFile(filename: "/usr/include/signal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!15 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !16, line: 133, baseType: !17)
!16 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!17 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!18 = !DIDerivedType(tag: DW_TAG_member, name: "child_stdin", scope: !10, file: !1, line: 67, baseType: !17, size: 32, align: 32, offset: 32)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "child_stdout", scope: !10, file: !1, line: 67, baseType: !17, size: 32, align: 32, offset: 64)
!20 = !DIDerivedType(tag: DW_TAG_member, name: "child_buf", scope: !10, file: !1, line: 69, baseType: !21, size: 64, align: 64, offset: 128)
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!22 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "child_buf_len", scope: !10, file: !1, line: 70, baseType: !24, size: 64, align: 64, offset: 192)
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !25, line: 62, baseType: !26)
!25 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!26 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "child_buf_avail", scope: !10, file: !1, line: 70, baseType: !24, size: 64, align: 64, offset: 256)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "program_name", scope: !10, file: !1, line: 71, baseType: !21, size: 64, align: 64, offset: 320)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "description", scope: !6, file: !1, line: 76, baseType: !30, size: 192, align: 64, offset: 64)
!30 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !31, line: 58, size: 192, align: 64, elements: !32)
!31 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!32 = !{!33, !34, !35}
!33 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !30, file: !31, line: 59, baseType: !21, size: 64, align: 64)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !30, file: !31, line: 60, baseType: !24, size: 64, align: 64, offset: 64)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !30, file: !31, line: 61, baseType: !24, size: 64, align: 64, offset: 128)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "cmd", scope: !6, file: !1, line: 77, baseType: !21, size: 64, align: 64, offset: 256)
!37 = !{!38, !129, !130, !133, !136, !165, !168, !171, !172, !173, !174, !175}
!38 = distinct !DISubprogram(name: "archive_write_set_compression_program", scope: !1, file: !1, line: 54, type: !39, isLocal: false, isDefinition: true, scopeLine: 55, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!39 = !DISubroutineType(types: !40)
!40 = !{!17, !41, !107}
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !43, line: 89, size: 1280, align: 64, elements: !44)
!43 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!44 = !{!45, !47, !48, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !123, !124, !125, !126, !127, !128}
!45 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !42, file: !43, line: 96, baseType: !46, size: 32, align: 32)
!46 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !42, file: !43, line: 97, baseType: !46, size: 32, align: 32, offset: 32)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !42, file: !43, line: 103, baseType: !49, size: 64, align: 64, offset: 64)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !43, line: 63, size: 832, align: 64, elements: !51)
!51 = !{!52, !56, !57, !64, !65, !75, !81, !86, !87, !94, !95, !99, !103}
!52 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !50, file: !43, line: 64, baseType: !53, size: 64, align: 64)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DISubroutineType(types: !55)
!55 = !{!17, !41}
!56 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !50, file: !43, line: 65, baseType: !53, size: 64, align: 64, offset: 64)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !50, file: !43, line: 66, baseType: !58, size: 64, align: 64, offset: 128)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!59 = !DISubroutineType(types: !60)
!60 = !{!17, !41, !61}
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !63, line: 180, flags: DIFlagFwdDecl)
!63 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!64 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !50, file: !43, line: 68, baseType: !53, size: 64, align: 64, offset: 192)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !50, file: !43, line: 69, baseType: !66, size: 64, align: 64, offset: 256)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DISubroutineType(types: !68)
!68 = !{!69, !41, !73, !24}
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !70, line: 109, baseType: !71)
!70 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !16, line: 172, baseType: !72)
!72 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !50, file: !43, line: 71, baseType: !76, size: 64, align: 64, offset: 320)
!76 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !77, size: 64, align: 64)
!77 = !DISubroutineType(types: !78)
!78 = !{!69, !41, !73, !24, !79}
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !80, line: 40, baseType: !72)
!80 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!81 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !50, file: !43, line: 74, baseType: !82, size: 64, align: 64, offset: 384)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DISubroutineType(types: !84)
!84 = !{!17, !41, !85}
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !50, file: !43, line: 76, baseType: !58, size: 64, align: 64, offset: 448)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !50, file: !43, line: 78, baseType: !88, size: 64, align: 64, offset: 512)
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!89 = !DISubroutineType(types: !90)
!90 = !{!17, !41, !91, !92, !93}
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !73, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !50, file: !43, line: 81, baseType: !53, size: 64, align: 64, offset: 576)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !50, file: !43, line: 82, baseType: !96, size: 64, align: 64, offset: 640)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DISubroutineType(types: !98)
!98 = !{!79, !41, !17}
!99 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !50, file: !43, line: 83, baseType: !100, size: 64, align: 64, offset: 704)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{!17, !41, !17}
!103 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !50, file: !43, line: 84, baseType: !104, size: 64, align: 64, offset: 768)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DISubroutineType(types: !106)
!106 = !{!107, !41, !17}
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !22)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !42, file: !43, line: 105, baseType: !17, size: 32, align: 32, offset: 128)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !42, file: !43, line: 106, baseType: !107, size: 64, align: 64, offset: 192)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !42, file: !43, line: 108, baseType: !17, size: 32, align: 32, offset: 256)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !42, file: !43, line: 109, baseType: !107, size: 64, align: 64, offset: 320)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !42, file: !43, line: 112, baseType: !17, size: 32, align: 32, offset: 384)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !42, file: !43, line: 114, baseType: !17, size: 32, align: 32, offset: 416)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !42, file: !43, line: 115, baseType: !107, size: 64, align: 64, offset: 448)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !42, file: !43, line: 116, baseType: !30, size: 192, align: 64, offset: 512)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !42, file: !43, line: 118, baseType: !21, size: 64, align: 64, offset: 704)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !42, file: !43, line: 119, baseType: !46, size: 32, align: 32, offset: 768)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !42, file: !43, line: 120, baseType: !46, size: 32, align: 32, offset: 800)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !42, file: !43, line: 121, baseType: !121, size: 64, align: 64, offset: 832)
!121 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!122 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !31, line: 70, flags: DIFlagFwdDecl)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !42, file: !43, line: 127, baseType: !107, size: 64, align: 64, offset: 896)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !42, file: !43, line: 128, baseType: !79, size: 64, align: 64, offset: 960)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !42, file: !43, line: 129, baseType: !79, size: 64, align: 64, offset: 1024)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !42, file: !43, line: 130, baseType: !24, size: 64, align: 64, offset: 1088)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !42, file: !43, line: 137, baseType: !22, size: 8, align: 8, offset: 1152)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !42, file: !43, line: 138, baseType: !24, size: 64, align: 64, offset: 1216)
!129 = distinct !DISubprogram(name: "archive_write_add_filter_program", scope: !1, file: !1, line: 91, type: !39, isLocal: false, isDefinition: true, scopeLine: 92, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!130 = distinct !DISubprogram(name: "__archive_write_program_allocate", scope: !1, file: !1, line: 178, type: !131, isLocal: false, isDefinition: true, scopeLine: 179, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!131 = !DISubroutineType(types: !132)
!132 = !{!9, !107}
!133 = distinct !DISubprogram(name: "__archive_write_program_free", scope: !1, file: !1, line: 195, type: !134, isLocal: false, isDefinition: true, scopeLine: 196, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!134 = !DISubroutineType(types: !135)
!135 = !{!17, !9}
!136 = distinct !DISubprogram(name: "__archive_write_program_open", scope: !1, file: !1, line: 211, type: !137, isLocal: false, isDefinition: true, scopeLine: 213, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!137 = !DISubroutineType(types: !138)
!138 = !{!17, !139, !9, !107}
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !141, line: 43, size: 768, align: 64, elements: !142)
!141 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!142 = !{!143, !144, !145, !146, !150, !154, !158, !159, !160, !161, !162, !163, !164}
!143 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !140, file: !141, line: 44, baseType: !79, size: 64, align: 64)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !140, file: !141, line: 45, baseType: !41, size: 64, align: 64, offset: 64)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !140, file: !141, line: 46, baseType: !139, size: 64, align: 64, offset: 128)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !140, file: !141, line: 47, baseType: !147, size: 64, align: 64, offset: 192)
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!148 = !DISubroutineType(types: !149)
!149 = !{!17, !139, !107, !107}
!150 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !140, file: !141, line: 49, baseType: !151, size: 64, align: 64, offset: 256)
!151 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !152, size: 64, align: 64)
!152 = !DISubroutineType(types: !153)
!153 = !{!17, !139}
!154 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !140, file: !141, line: 50, baseType: !155, size: 64, align: 64, offset: 320)
!155 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !156, size: 64, align: 64)
!156 = !DISubroutineType(types: !157)
!157 = !{!17, !139, !73, !24}
!158 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !140, file: !141, line: 51, baseType: !151, size: 64, align: 64, offset: 384)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !140, file: !141, line: 52, baseType: !151, size: 64, align: 64, offset: 448)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !140, file: !141, line: 53, baseType: !4, size: 64, align: 64, offset: 512)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !140, file: !141, line: 54, baseType: !107, size: 64, align: 64, offset: 576)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !140, file: !141, line: 55, baseType: !17, size: 32, align: 32, offset: 640)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !140, file: !141, line: 56, baseType: !17, size: 32, align: 32, offset: 672)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !140, file: !141, line: 57, baseType: !17, size: 32, align: 32, offset: 704)
!165 = distinct !DISubprogram(name: "__archive_write_program_write", scope: !1, file: !1, line: 326, type: !166, isLocal: false, isDefinition: true, scopeLine: 328, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!166 = !DISubroutineType(types: !167)
!167 = !{!17, !139, !9, !73, !24}
!168 = distinct !DISubprogram(name: "__archive_write_program_close", scope: !1, file: !1, line: 353, type: !169, isLocal: false, isDefinition: true, scopeLine: 355, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!169 = !DISubroutineType(types: !170)
!170 = !{!17, !139, !9}
!171 = distinct !DISubprogram(name: "archive_compressor_program_open", scope: !1, file: !1, line: 135, type: !152, isLocal: true, isDefinition: true, scopeLine: 136, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!172 = distinct !DISubprogram(name: "archive_compressor_program_write", scope: !1, file: !1, line: 143, type: !156, isLocal: true, isDefinition: true, scopeLine: 145, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!173 = distinct !DISubprogram(name: "archive_compressor_program_close", scope: !1, file: !1, line: 152, type: !152, isLocal: true, isDefinition: true, scopeLine: 153, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!174 = distinct !DISubprogram(name: "archive_compressor_program_free", scope: !1, file: !1, line: 160, type: !152, isLocal: true, isDefinition: true, scopeLine: 161, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!175 = distinct !DISubprogram(name: "child_write", scope: !1, file: !1, line: 258, type: !176, isLocal: true, isDefinition: true, scopeLine: 260, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!176 = !DISubroutineType(types: !177)
!177 = !{!69, !139, !9, !107, !24}
!178 = !{!179}
!179 = !DIGlobalVariable(name: "prefix", scope: !129, file: !1, line: 95, type: !107, isLocal: true, isDefinition: true, variable: i8** @archive_write_add_filter_program.prefix)
!180 = !{i32 2, !"Dwarf Version", i32 4}
!181 = !{i32 2, !"Debug Info Version", i32 3}
!182 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!183 = !DILocalVariable(name: "a", arg: 1, scope: !38, file: !1, line: 54, type: !41)
!184 = !DIExpression()
!185 = !DILocation(line: 54, column: 55, scope: !38)
!186 = !DILocalVariable(name: "cmd", arg: 2, scope: !38, file: !1, line: 54, type: !107)
!187 = !DILocation(line: 54, column: 70, scope: !38)
!188 = !DILocation(line: 56, column: 31, scope: !38)
!189 = !DILocation(line: 56, column: 2, scope: !38)
!190 = !DILocation(line: 57, column: 43, scope: !38)
!191 = !DILocation(line: 57, column: 46, scope: !38)
!192 = !DILocation(line: 57, column: 10, scope: !38)
!193 = !DILocation(line: 57, column: 2, scope: !38)
!194 = !DILocalVariable(name: "_a", arg: 1, scope: !129, file: !1, line: 91, type: !41)
!195 = !DILocation(line: 91, column: 50, scope: !129)
!196 = !DILocalVariable(name: "cmd", arg: 2, scope: !129, file: !1, line: 91, type: !107)
!197 = !DILocation(line: 91, column: 66, scope: !129)
!198 = !DILocalVariable(name: "f", scope: !129, file: !1, line: 93, type: !139)
!199 = !DILocation(line: 93, column: 31, scope: !129)
!200 = !DILocation(line: 93, column: 67, scope: !129)
!201 = !DILocation(line: 93, column: 35, scope: !129)
!202 = !DILocalVariable(name: "data", scope: !129, file: !1, line: 94, type: !5)
!203 = !DILocation(line: 94, column: 23, scope: !129)
!204 = !DILocation(line: 97, column: 2, scope: !129)
!205 = !DILocalVariable(name: "magic_test", scope: !206, file: !1, line: 97, type: !17)
!206 = distinct !DILexicalBlock(scope: !129, file: !1, line: 97, column: 2)
!207 = !DILocation(line: 97, column: 2, scope: !206)
!208 = !DILocation(line: 97, column: 2, scope: !209)
!209 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 1)
!210 = !DILocation(line: 97, column: 2, scope: !211)
!211 = !DILexicalBlockFile(scope: !212, file: !1, discriminator: 2)
!212 = distinct !DILexicalBlock(scope: !206, file: !1, line: 97, column: 2)
!213 = !DILocation(line: 97, column: 2, scope: !214)
!214 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 3)
!215 = !DILocation(line: 100, column: 12, scope: !129)
!216 = !DILocation(line: 100, column: 2, scope: !129)
!217 = !DILocation(line: 100, column: 5, scope: !129)
!218 = !DILocation(line: 100, column: 10, scope: !129)
!219 = !DILocation(line: 101, column: 6, scope: !220)
!220 = distinct !DILexicalBlock(scope: !129, file: !1, line: 101, column: 6)
!221 = !DILocation(line: 101, column: 9, scope: !220)
!222 = !DILocation(line: 101, column: 14, scope: !220)
!223 = !DILocation(line: 101, column: 6, scope: !129)
!224 = !DILocation(line: 102, column: 3, scope: !220)
!225 = !DILocation(line: 103, column: 32, scope: !129)
!226 = !DILocation(line: 103, column: 35, scope: !129)
!227 = !DILocation(line: 103, column: 9, scope: !129)
!228 = !DILocation(line: 103, column: 7, scope: !129)
!229 = !DILocation(line: 105, column: 21, scope: !129)
!230 = !DILocation(line: 105, column: 14, scope: !129)
!231 = !DILocation(line: 105, column: 2, scope: !129)
!232 = !DILocation(line: 105, column: 8, scope: !129)
!233 = !DILocation(line: 105, column: 12, scope: !129)
!234 = !DILocation(line: 106, column: 6, scope: !235)
!235 = distinct !DILexicalBlock(scope: !129, file: !1, line: 106, column: 6)
!236 = !DILocation(line: 106, column: 12, scope: !235)
!237 = !DILocation(line: 106, column: 16, scope: !235)
!238 = !DILocation(line: 106, column: 6, scope: !129)
!239 = !DILocation(line: 107, column: 3, scope: !235)
!240 = !DILocation(line: 109, column: 49, scope: !129)
!241 = !DILocation(line: 109, column: 16, scope: !129)
!242 = !DILocation(line: 109, column: 2, scope: !129)
!243 = !DILocation(line: 109, column: 8, scope: !129)
!244 = !DILocation(line: 109, column: 14, scope: !129)
!245 = !DILocation(line: 110, column: 6, scope: !246)
!246 = distinct !DILexicalBlock(scope: !129, file: !1, line: 110, column: 6)
!247 = !DILocation(line: 110, column: 12, scope: !246)
!248 = !DILocation(line: 110, column: 18, scope: !246)
!249 = !DILocation(line: 110, column: 6, scope: !129)
!250 = !DILocation(line: 111, column: 3, scope: !246)
!251 = !DILocation(line: 114, column: 29, scope: !252)
!252 = distinct !DILexicalBlock(scope: !129, file: !1, line: 114, column: 6)
!253 = !DILocation(line: 114, column: 35, scope: !252)
!254 = !DILocation(line: 115, column: 13, scope: !252)
!255 = !DILocation(line: 115, column: 6, scope: !252)
!256 = !DILocation(line: 115, column: 30, scope: !252)
!257 = !DILocation(line: 115, column: 23, scope: !258)
!258 = !DILexicalBlockFile(scope: !252, file: !1, discriminator: 1)
!259 = !DILocation(line: 115, column: 21, scope: !252)
!260 = !DILocation(line: 115, column: 35, scope: !252)
!261 = !DILocation(line: 114, column: 6, scope: !252)
!262 = !DILocation(line: 115, column: 40, scope: !252)
!263 = !DILocation(line: 114, column: 6, scope: !129)
!264 = !DILocation(line: 116, column: 3, scope: !252)
!265 = !DILocation(line: 117, column: 2, scope: !129)
!266 = !DILocation(line: 117, column: 2, scope: !267)
!267 = !DILexicalBlockFile(scope: !129, file: !1, discriminator: 1)
!268 = !DILocation(line: 117, column: 2, scope: !269)
!269 = !DILexicalBlockFile(scope: !129, file: !1, discriminator: 2)
!270 = !DILocation(line: 117, column: 2, scope: !271)
!271 = !DILexicalBlockFile(scope: !129, file: !1, discriminator: 3)
!272 = !DILocation(line: 118, column: 18, scope: !129)
!273 = !DILocation(line: 118, column: 24, scope: !129)
!274 = !DILocation(line: 118, column: 37, scope: !129)
!275 = !DILocation(line: 118, column: 2, scope: !129)
!276 = !DILocation(line: 120, column: 12, scope: !129)
!277 = !DILocation(line: 120, column: 18, scope: !129)
!278 = !DILocation(line: 120, column: 30, scope: !129)
!279 = !DILocation(line: 120, column: 2, scope: !129)
!280 = !DILocation(line: 120, column: 5, scope: !129)
!281 = !DILocation(line: 120, column: 10, scope: !129)
!282 = !DILocation(line: 121, column: 2, scope: !129)
!283 = !DILocation(line: 121, column: 5, scope: !129)
!284 = !DILocation(line: 121, column: 10, scope: !129)
!285 = !DILocation(line: 122, column: 2, scope: !129)
!286 = !DILocation(line: 122, column: 5, scope: !129)
!287 = !DILocation(line: 122, column: 10, scope: !129)
!288 = !DILocation(line: 123, column: 2, scope: !129)
!289 = !DILocation(line: 123, column: 5, scope: !129)
!290 = !DILocation(line: 123, column: 11, scope: !129)
!291 = !DILocation(line: 124, column: 2, scope: !129)
!292 = !DILocation(line: 124, column: 5, scope: !129)
!293 = !DILocation(line: 124, column: 11, scope: !129)
!294 = !DILocation(line: 125, column: 2, scope: !129)
!295 = !DILocation(line: 125, column: 5, scope: !129)
!296 = !DILocation(line: 125, column: 10, scope: !129)
!297 = !DILocation(line: 126, column: 2, scope: !129)
!298 = !DILocation(line: 128, column: 34, scope: !129)
!299 = !DILocation(line: 128, column: 2, scope: !129)
!300 = !DILocation(line: 129, column: 20, scope: !129)
!301 = !DILocation(line: 129, column: 2, scope: !129)
!302 = !DILocation(line: 131, column: 2, scope: !129)
!303 = !DILocation(line: 132, column: 1, scope: !129)
!304 = !DILocalVariable(name: "program", arg: 1, scope: !130, file: !1, line: 178, type: !107)
!305 = !DILocation(line: 178, column: 46, scope: !130)
!306 = !DILocalVariable(name: "data", scope: !130, file: !1, line: 180, type: !9)
!307 = !DILocation(line: 180, column: 37, scope: !130)
!308 = !DILocation(line: 182, column: 9, scope: !130)
!309 = !DILocation(line: 182, column: 7, scope: !130)
!310 = !DILocation(line: 183, column: 6, scope: !311)
!311 = distinct !DILexicalBlock(scope: !130, file: !1, line: 183, column: 6)
!312 = !DILocation(line: 183, column: 11, scope: !311)
!313 = !DILocation(line: 183, column: 6, scope: !130)
!314 = !DILocation(line: 184, column: 11, scope: !311)
!315 = !DILocation(line: 184, column: 3, scope: !311)
!316 = !DILocation(line: 185, column: 2, scope: !130)
!317 = !DILocation(line: 185, column: 8, scope: !130)
!318 = !DILocation(line: 185, column: 20, scope: !130)
!319 = !DILocation(line: 186, column: 2, scope: !130)
!320 = !DILocation(line: 186, column: 8, scope: !130)
!321 = !DILocation(line: 186, column: 21, scope: !130)
!322 = !DILocation(line: 187, column: 30, scope: !130)
!323 = !DILocation(line: 187, column: 23, scope: !130)
!324 = !DILocation(line: 187, column: 2, scope: !130)
!325 = !DILocation(line: 187, column: 8, scope: !130)
!326 = !DILocation(line: 187, column: 21, scope: !130)
!327 = !DILocation(line: 188, column: 10, scope: !130)
!328 = !DILocation(line: 188, column: 2, scope: !130)
!329 = !DILocation(line: 189, column: 1, scope: !130)
!330 = !DILocalVariable(name: "f", arg: 1, scope: !171, file: !1, line: 135, type: !139)
!331 = !DILocation(line: 135, column: 62, scope: !171)
!332 = !DILocalVariable(name: "data", scope: !171, file: !1, line: 137, type: !5)
!333 = !DILocation(line: 137, column: 23, scope: !171)
!334 = !DILocation(line: 137, column: 53, scope: !171)
!335 = !DILocation(line: 137, column: 56, scope: !171)
!336 = !DILocation(line: 137, column: 30, scope: !171)
!337 = !DILocation(line: 139, column: 38, scope: !171)
!338 = !DILocation(line: 139, column: 41, scope: !171)
!339 = !DILocation(line: 139, column: 47, scope: !171)
!340 = !DILocation(line: 139, column: 54, scope: !171)
!341 = !DILocation(line: 139, column: 60, scope: !171)
!342 = !DILocation(line: 139, column: 9, scope: !171)
!343 = !DILocation(line: 139, column: 2, scope: !171)
!344 = !DILocalVariable(name: "f", arg: 1, scope: !172, file: !1, line: 143, type: !139)
!345 = !DILocation(line: 143, column: 63, scope: !172)
!346 = !DILocalVariable(name: "buff", arg: 2, scope: !172, file: !1, line: 144, type: !73)
!347 = !DILocation(line: 144, column: 17, scope: !172)
!348 = !DILocalVariable(name: "length", arg: 3, scope: !172, file: !1, line: 144, type: !24)
!349 = !DILocation(line: 144, column: 30, scope: !172)
!350 = !DILocalVariable(name: "data", scope: !172, file: !1, line: 146, type: !5)
!351 = !DILocation(line: 146, column: 23, scope: !172)
!352 = !DILocation(line: 146, column: 53, scope: !172)
!353 = !DILocation(line: 146, column: 56, scope: !172)
!354 = !DILocation(line: 146, column: 30, scope: !172)
!355 = !DILocation(line: 148, column: 39, scope: !172)
!356 = !DILocation(line: 148, column: 42, scope: !172)
!357 = !DILocation(line: 148, column: 48, scope: !172)
!358 = !DILocation(line: 148, column: 55, scope: !172)
!359 = !DILocation(line: 148, column: 61, scope: !172)
!360 = !DILocation(line: 148, column: 9, scope: !172)
!361 = !DILocation(line: 148, column: 2, scope: !172)
!362 = !DILocalVariable(name: "f", arg: 1, scope: !173, file: !1, line: 152, type: !139)
!363 = !DILocation(line: 152, column: 63, scope: !173)
!364 = !DILocalVariable(name: "data", scope: !173, file: !1, line: 154, type: !5)
!365 = !DILocation(line: 154, column: 23, scope: !173)
!366 = !DILocation(line: 154, column: 53, scope: !173)
!367 = !DILocation(line: 154, column: 56, scope: !173)
!368 = !DILocation(line: 154, column: 30, scope: !173)
!369 = !DILocation(line: 156, column: 39, scope: !173)
!370 = !DILocation(line: 156, column: 42, scope: !173)
!371 = !DILocation(line: 156, column: 48, scope: !173)
!372 = !DILocation(line: 156, column: 9, scope: !173)
!373 = !DILocation(line: 156, column: 2, scope: !173)
!374 = !DILocalVariable(name: "f", arg: 1, scope: !174, file: !1, line: 160, type: !139)
!375 = !DILocation(line: 160, column: 62, scope: !174)
!376 = !DILocalVariable(name: "data", scope: !174, file: !1, line: 162, type: !5)
!377 = !DILocation(line: 162, column: 23, scope: !174)
!378 = !DILocation(line: 162, column: 53, scope: !174)
!379 = !DILocation(line: 162, column: 56, scope: !174)
!380 = !DILocation(line: 162, column: 30, scope: !174)
!381 = !DILocation(line: 164, column: 6, scope: !382)
!382 = distinct !DILexicalBlock(scope: !174, file: !1, line: 164, column: 6)
!383 = !DILocation(line: 164, column: 6, scope: !174)
!384 = !DILocation(line: 165, column: 8, scope: !385)
!385 = distinct !DILexicalBlock(scope: !382, file: !1, line: 164, column: 12)
!386 = !DILocation(line: 165, column: 14, scope: !385)
!387 = !DILocation(line: 165, column: 3, scope: !385)
!388 = !DILocation(line: 166, column: 24, scope: !385)
!389 = !DILocation(line: 166, column: 30, scope: !385)
!390 = !DILocation(line: 166, column: 3, scope: !385)
!391 = !DILocation(line: 167, column: 32, scope: !385)
!392 = !DILocation(line: 167, column: 38, scope: !385)
!393 = !DILocation(line: 167, column: 3, scope: !385)
!394 = !DILocation(line: 168, column: 8, scope: !385)
!395 = !DILocation(line: 168, column: 3, scope: !385)
!396 = !DILocation(line: 169, column: 3, scope: !385)
!397 = !DILocation(line: 169, column: 6, scope: !385)
!398 = !DILocation(line: 169, column: 11, scope: !385)
!399 = !DILocation(line: 170, column: 2, scope: !385)
!400 = !DILocation(line: 171, column: 2, scope: !174)
!401 = !DILocalVariable(name: "data", arg: 1, scope: !133, file: !1, line: 195, type: !9)
!402 = !DILocation(line: 195, column: 65, scope: !133)
!403 = !DILocation(line: 198, column: 6, scope: !404)
!404 = distinct !DILexicalBlock(scope: !133, file: !1, line: 198, column: 6)
!405 = !DILocation(line: 198, column: 6, scope: !133)
!406 = !DILocation(line: 203, column: 8, scope: !407)
!407 = distinct !DILexicalBlock(scope: !404, file: !1, line: 198, column: 12)
!408 = !DILocation(line: 203, column: 14, scope: !407)
!409 = !DILocation(line: 203, column: 3, scope: !407)
!410 = !DILocation(line: 204, column: 8, scope: !407)
!411 = !DILocation(line: 204, column: 14, scope: !407)
!412 = !DILocation(line: 204, column: 3, scope: !407)
!413 = !DILocation(line: 205, column: 8, scope: !407)
!414 = !DILocation(line: 205, column: 3, scope: !407)
!415 = !DILocation(line: 206, column: 2, scope: !407)
!416 = !DILocation(line: 207, column: 2, scope: !133)
!417 = !DILocalVariable(name: "f", arg: 1, scope: !136, file: !1, line: 211, type: !139)
!418 = !DILocation(line: 211, column: 59, scope: !136)
!419 = !DILocalVariable(name: "data", arg: 2, scope: !136, file: !1, line: 212, type: !9)
!420 = !DILocation(line: 212, column: 40, scope: !136)
!421 = !DILocalVariable(name: "cmd", arg: 3, scope: !136, file: !1, line: 212, type: !107)
!422 = !DILocation(line: 212, column: 58, scope: !136)
!423 = !DILocalVariable(name: "child", scope: !136, file: !1, line: 214, type: !13)
!424 = !DILocation(line: 214, column: 8, scope: !136)
!425 = !DILocalVariable(name: "ret", scope: !136, file: !1, line: 215, type: !17)
!426 = !DILocation(line: 215, column: 6, scope: !136)
!427 = !DILocation(line: 217, column: 36, scope: !136)
!428 = !DILocation(line: 217, column: 39, scope: !136)
!429 = !DILocation(line: 217, column: 8, scope: !136)
!430 = !DILocation(line: 217, column: 6, scope: !136)
!431 = !DILocation(line: 218, column: 6, scope: !432)
!432 = distinct !DILexicalBlock(scope: !136, file: !1, line: 218, column: 6)
!433 = !DILocation(line: 218, column: 10, scope: !432)
!434 = !DILocation(line: 218, column: 6, scope: !136)
!435 = !DILocation(line: 219, column: 11, scope: !432)
!436 = !DILocation(line: 219, column: 3, scope: !432)
!437 = !DILocation(line: 221, column: 6, scope: !438)
!438 = distinct !DILexicalBlock(scope: !136, file: !1, line: 221, column: 6)
!439 = !DILocation(line: 221, column: 12, scope: !438)
!440 = !DILocation(line: 221, column: 22, scope: !438)
!441 = !DILocation(line: 221, column: 6, scope: !136)
!442 = !DILocation(line: 222, column: 3, scope: !443)
!443 = distinct !DILexicalBlock(scope: !438, file: !1, line: 221, column: 31)
!444 = !DILocation(line: 222, column: 9, scope: !443)
!445 = !DILocation(line: 222, column: 23, scope: !443)
!446 = !DILocation(line: 223, column: 3, scope: !443)
!447 = !DILocation(line: 223, column: 9, scope: !443)
!448 = !DILocation(line: 223, column: 25, scope: !443)
!449 = !DILocation(line: 224, column: 28, scope: !443)
!450 = !DILocation(line: 224, column: 34, scope: !443)
!451 = !DILocation(line: 224, column: 21, scope: !443)
!452 = !DILocation(line: 224, column: 3, scope: !443)
!453 = !DILocation(line: 224, column: 9, scope: !443)
!454 = !DILocation(line: 224, column: 19, scope: !443)
!455 = !DILocation(line: 226, column: 7, scope: !456)
!456 = distinct !DILexicalBlock(scope: !443, file: !1, line: 226, column: 7)
!457 = !DILocation(line: 226, column: 13, scope: !456)
!458 = !DILocation(line: 226, column: 23, scope: !456)
!459 = !DILocation(line: 226, column: 7, scope: !443)
!460 = !DILocation(line: 227, column: 22, scope: !461)
!461 = distinct !DILexicalBlock(scope: !456, file: !1, line: 226, column: 32)
!462 = !DILocation(line: 227, column: 25, scope: !461)
!463 = !DILocation(line: 227, column: 4, scope: !461)
!464 = !DILocation(line: 229, column: 4, scope: !461)
!465 = !DILocation(line: 231, column: 2, scope: !443)
!466 = !DILocation(line: 233, column: 33, scope: !136)
!467 = !DILocation(line: 233, column: 39, scope: !136)
!468 = !DILocation(line: 233, column: 45, scope: !136)
!469 = !DILocation(line: 234, column: 8, scope: !136)
!470 = !DILocation(line: 234, column: 14, scope: !136)
!471 = !DILocation(line: 233, column: 10, scope: !136)
!472 = !DILocation(line: 233, column: 8, scope: !136)
!473 = !DILocation(line: 235, column: 6, scope: !474)
!474 = distinct !DILexicalBlock(scope: !136, file: !1, line: 235, column: 6)
!475 = !DILocation(line: 235, column: 12, scope: !474)
!476 = !DILocation(line: 235, column: 6, scope: !136)
!477 = !DILocation(line: 236, column: 21, scope: !478)
!478 = distinct !DILexicalBlock(scope: !474, file: !1, line: 235, column: 19)
!479 = !DILocation(line: 236, column: 24, scope: !478)
!480 = !DILocation(line: 237, column: 44, scope: !478)
!481 = !DILocation(line: 236, column: 3, scope: !478)
!482 = !DILocation(line: 238, column: 3, scope: !478)
!483 = !DILocation(line: 252, column: 16, scope: !136)
!484 = !DILocation(line: 252, column: 2, scope: !136)
!485 = !DILocation(line: 252, column: 8, scope: !136)
!486 = !DILocation(line: 252, column: 14, scope: !136)
!487 = !DILocation(line: 254, column: 2, scope: !136)
!488 = !DILocation(line: 255, column: 1, scope: !136)
!489 = !DILocalVariable(name: "f", arg: 1, scope: !165, file: !1, line: 326, type: !139)
!490 = !DILocation(line: 326, column: 60, scope: !165)
!491 = !DILocalVariable(name: "data", arg: 2, scope: !165, file: !1, line: 327, type: !9)
!492 = !DILocation(line: 327, column: 40, scope: !165)
!493 = !DILocalVariable(name: "buff", arg: 3, scope: !165, file: !1, line: 327, type: !73)
!494 = !DILocation(line: 327, column: 58, scope: !165)
!495 = !DILocalVariable(name: "length", arg: 4, scope: !165, file: !1, line: 327, type: !24)
!496 = !DILocation(line: 327, column: 71, scope: !165)
!497 = !DILocalVariable(name: "ret", scope: !165, file: !1, line: 329, type: !69)
!498 = !DILocation(line: 329, column: 10, scope: !165)
!499 = !DILocalVariable(name: "buf", scope: !165, file: !1, line: 330, type: !107)
!500 = !DILocation(line: 330, column: 14, scope: !165)
!501 = !DILocation(line: 332, column: 6, scope: !502)
!502 = distinct !DILexicalBlock(scope: !165, file: !1, line: 332, column: 6)
!503 = !DILocation(line: 332, column: 12, scope: !502)
!504 = !DILocation(line: 332, column: 18, scope: !502)
!505 = !DILocation(line: 332, column: 6, scope: !165)
!506 = !DILocation(line: 333, column: 3, scope: !502)
!507 = !DILocation(line: 335, column: 8, scope: !165)
!508 = !DILocation(line: 335, column: 6, scope: !165)
!509 = !DILocation(line: 336, column: 2, scope: !165)
!510 = !DILocation(line: 336, column: 9, scope: !511)
!511 = !DILexicalBlockFile(scope: !165, file: !1, discriminator: 1)
!512 = !DILocation(line: 336, column: 16, scope: !511)
!513 = !DILocation(line: 336, column: 2, scope: !511)
!514 = !DILocation(line: 337, column: 21, scope: !515)
!515 = distinct !DILexicalBlock(scope: !165, file: !1, line: 336, column: 21)
!516 = !DILocation(line: 337, column: 24, scope: !515)
!517 = !DILocation(line: 337, column: 30, scope: !515)
!518 = !DILocation(line: 337, column: 35, scope: !515)
!519 = !DILocation(line: 337, column: 9, scope: !515)
!520 = !DILocation(line: 337, column: 7, scope: !515)
!521 = !DILocation(line: 338, column: 7, scope: !522)
!522 = distinct !DILexicalBlock(scope: !515, file: !1, line: 338, column: 7)
!523 = !DILocation(line: 338, column: 11, scope: !522)
!524 = !DILocation(line: 338, column: 17, scope: !522)
!525 = !DILocation(line: 338, column: 20, scope: !526)
!526 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 1)
!527 = !DILocation(line: 338, column: 24, scope: !526)
!528 = !DILocation(line: 338, column: 7, scope: !526)
!529 = !DILocation(line: 339, column: 22, scope: !530)
!530 = distinct !DILexicalBlock(scope: !522, file: !1, line: 338, column: 30)
!531 = !DILocation(line: 339, column: 25, scope: !530)
!532 = !DILocation(line: 340, column: 38, scope: !530)
!533 = !DILocation(line: 340, column: 44, scope: !530)
!534 = !DILocation(line: 339, column: 4, scope: !530)
!535 = !DILocation(line: 341, column: 4, scope: !530)
!536 = !DILocation(line: 343, column: 13, scope: !515)
!537 = !DILocation(line: 343, column: 10, scope: !515)
!538 = !DILocation(line: 344, column: 10, scope: !515)
!539 = !DILocation(line: 344, column: 7, scope: !515)
!540 = !DILocation(line: 336, column: 2, scope: !541)
!541 = !DILexicalBlockFile(scope: !165, file: !1, discriminator: 2)
!542 = !DILocation(line: 346, column: 2, scope: !165)
!543 = !DILocation(line: 347, column: 1, scope: !165)
!544 = !DILocalVariable(name: "f", arg: 1, scope: !175, file: !1, line: 258, type: !139)
!545 = !DILocation(line: 258, column: 42, scope: !175)
!546 = !DILocalVariable(name: "data", arg: 2, scope: !175, file: !1, line: 259, type: !9)
!547 = !DILocation(line: 259, column: 40, scope: !175)
!548 = !DILocalVariable(name: "buf", arg: 3, scope: !175, file: !1, line: 259, type: !107)
!549 = !DILocation(line: 259, column: 58, scope: !175)
!550 = !DILocalVariable(name: "buf_len", arg: 4, scope: !175, file: !1, line: 259, type: !24)
!551 = !DILocation(line: 259, column: 70, scope: !175)
!552 = !DILocalVariable(name: "ret", scope: !175, file: !1, line: 261, type: !69)
!553 = !DILocation(line: 261, column: 10, scope: !175)
!554 = !DILocation(line: 263, column: 6, scope: !555)
!555 = distinct !DILexicalBlock(scope: !175, file: !1, line: 263, column: 6)
!556 = !DILocation(line: 263, column: 12, scope: !555)
!557 = !DILocation(line: 263, column: 24, scope: !555)
!558 = !DILocation(line: 263, column: 6, scope: !175)
!559 = !DILocation(line: 264, column: 3, scope: !555)
!560 = !DILocation(line: 266, column: 6, scope: !561)
!561 = distinct !DILexicalBlock(scope: !175, file: !1, line: 266, column: 6)
!562 = !DILocation(line: 266, column: 14, scope: !561)
!563 = !DILocation(line: 266, column: 6, scope: !175)
!564 = !DILocation(line: 267, column: 3, scope: !561)
!565 = !DILocation(line: 269, column: 2, scope: !175)
!566 = !DILocation(line: 270, column: 3, scope: !567)
!567 = distinct !DILexicalBlock(scope: !568, file: !1, line: 269, column: 11)
!568 = distinct !DILexicalBlock(scope: !569, file: !1, line: 269, column: 2)
!569 = distinct !DILexicalBlock(scope: !175, file: !1, line: 269, column: 2)
!570 = !DILocation(line: 271, column: 16, scope: !571)
!571 = distinct !DILexicalBlock(scope: !567, file: !1, line: 270, column: 6)
!572 = !DILocation(line: 271, column: 22, scope: !571)
!573 = !DILocation(line: 271, column: 35, scope: !571)
!574 = !DILocation(line: 271, column: 40, scope: !571)
!575 = !DILocation(line: 271, column: 10, scope: !571)
!576 = !DILocation(line: 271, column: 8, scope: !571)
!577 = !DILocation(line: 272, column: 3, scope: !571)
!578 = !DILocation(line: 272, column: 12, scope: !579)
!579 = !DILexicalBlockFile(scope: !567, file: !1, discriminator: 1)
!580 = !DILocation(line: 272, column: 16, scope: !579)
!581 = !DILocation(line: 272, column: 22, scope: !579)
!582 = !DILocation(line: 272, column: 25, scope: !583)
!583 = !DILexicalBlockFile(scope: !567, file: !1, discriminator: 2)
!584 = !DILocation(line: 272, column: 31, scope: !583)
!585 = !DILocation(line: 272, column: 3, scope: !586)
!586 = !DILexicalBlockFile(scope: !571, file: !1, discriminator: 3)
!587 = !DILocation(line: 274, column: 7, scope: !588)
!588 = distinct !DILexicalBlock(scope: !567, file: !1, line: 274, column: 7)
!589 = !DILocation(line: 274, column: 11, scope: !588)
!590 = !DILocation(line: 274, column: 7, scope: !567)
!591 = !DILocation(line: 275, column: 12, scope: !588)
!592 = !DILocation(line: 275, column: 4, scope: !588)
!593 = !DILocation(line: 276, column: 7, scope: !594)
!594 = distinct !DILexicalBlock(scope: !567, file: !1, line: 276, column: 7)
!595 = !DILocation(line: 276, column: 11, scope: !594)
!596 = !DILocation(line: 276, column: 7, scope: !567)
!597 = !DILocation(line: 277, column: 10, scope: !598)
!598 = distinct !DILexicalBlock(scope: !594, file: !1, line: 276, column: 17)
!599 = !DILocation(line: 277, column: 16, scope: !598)
!600 = !DILocation(line: 277, column: 4, scope: !598)
!601 = !DILocation(line: 278, column: 4, scope: !598)
!602 = !DILocation(line: 278, column: 10, scope: !598)
!603 = !DILocation(line: 278, column: 22, scope: !598)
!604 = !DILocation(line: 279, column: 10, scope: !598)
!605 = !DILocation(line: 279, column: 16, scope: !598)
!606 = !DILocation(line: 279, column: 4, scope: !598)
!607 = !DILocation(line: 280, column: 4, scope: !598)
!608 = !DILocation(line: 282, column: 7, scope: !609)
!609 = distinct !DILexicalBlock(scope: !567, file: !1, line: 282, column: 7)
!610 = !DILocation(line: 282, column: 11, scope: !609)
!611 = !DILocation(line: 282, column: 17, scope: !609)
!612 = !DILocation(line: 282, column: 20, scope: !613)
!613 = !DILexicalBlockFile(scope: !609, file: !1, discriminator: 1)
!614 = !DILocation(line: 282, column: 26, scope: !613)
!615 = !DILocation(line: 282, column: 7, scope: !613)
!616 = !DILocation(line: 283, column: 4, scope: !609)
!617 = !DILocation(line: 285, column: 7, scope: !618)
!618 = distinct !DILexicalBlock(scope: !567, file: !1, line: 285, column: 7)
!619 = !DILocation(line: 285, column: 13, scope: !618)
!620 = !DILocation(line: 285, column: 26, scope: !618)
!621 = !DILocation(line: 285, column: 7, scope: !567)
!622 = !DILocation(line: 286, column: 10, scope: !623)
!623 = distinct !DILexicalBlock(scope: !618, file: !1, line: 285, column: 33)
!624 = !DILocation(line: 286, column: 16, scope: !623)
!625 = !DILocation(line: 286, column: 4, scope: !623)
!626 = !DILocation(line: 287, column: 26, scope: !623)
!627 = !DILocation(line: 287, column: 32, scope: !623)
!628 = !DILocation(line: 288, column: 5, scope: !623)
!629 = !DILocation(line: 288, column: 11, scope: !623)
!630 = !DILocation(line: 287, column: 4, scope: !623)
!631 = !DILocation(line: 289, column: 4, scope: !623)
!632 = !DILocation(line: 292, column: 3, scope: !567)
!633 = !DILocation(line: 293, column: 15, scope: !634)
!634 = distinct !DILexicalBlock(scope: !567, file: !1, line: 292, column: 6)
!635 = !DILocation(line: 293, column: 21, scope: !634)
!636 = !DILocation(line: 294, column: 8, scope: !634)
!637 = !DILocation(line: 294, column: 14, scope: !634)
!638 = !DILocation(line: 294, column: 26, scope: !634)
!639 = !DILocation(line: 294, column: 32, scope: !634)
!640 = !DILocation(line: 294, column: 24, scope: !634)
!641 = !DILocation(line: 295, column: 8, scope: !634)
!642 = !DILocation(line: 295, column: 14, scope: !634)
!643 = !DILocation(line: 295, column: 30, scope: !634)
!644 = !DILocation(line: 295, column: 36, scope: !634)
!645 = !DILocation(line: 295, column: 28, scope: !634)
!646 = !DILocation(line: 293, column: 10, scope: !634)
!647 = !DILocation(line: 293, column: 8, scope: !634)
!648 = !DILocation(line: 296, column: 3, scope: !634)
!649 = !DILocation(line: 296, column: 12, scope: !579)
!650 = !DILocation(line: 296, column: 16, scope: !579)
!651 = !DILocation(line: 296, column: 22, scope: !579)
!652 = !DILocation(line: 296, column: 25, scope: !583)
!653 = !DILocation(line: 296, column: 31, scope: !583)
!654 = !DILocation(line: 296, column: 3, scope: !655)
!655 = !DILexicalBlockFile(scope: !634, file: !1, discriminator: 3)
!656 = !DILocation(line: 298, column: 7, scope: !657)
!657 = distinct !DILexicalBlock(scope: !567, file: !1, line: 298, column: 7)
!658 = !DILocation(line: 298, column: 11, scope: !657)
!659 = !DILocation(line: 298, column: 16, scope: !657)
!660 = !DILocation(line: 298, column: 20, scope: !661)
!661 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 1)
!662 = !DILocation(line: 298, column: 24, scope: !661)
!663 = !DILocation(line: 298, column: 30, scope: !661)
!664 = !DILocation(line: 298, column: 33, scope: !665)
!665 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 2)
!666 = !DILocation(line: 298, column: 39, scope: !665)
!667 = !DILocation(line: 298, column: 7, scope: !665)
!668 = !DILocation(line: 299, column: 10, scope: !669)
!669 = distinct !DILexicalBlock(scope: !657, file: !1, line: 298, column: 50)
!670 = !DILocation(line: 299, column: 16, scope: !669)
!671 = !DILocation(line: 299, column: 4, scope: !669)
!672 = !DILocation(line: 300, column: 4, scope: !669)
!673 = !DILocation(line: 300, column: 10, scope: !669)
!674 = !DILocation(line: 300, column: 23, scope: !669)
!675 = !DILocation(line: 301, column: 10, scope: !669)
!676 = !DILocation(line: 301, column: 16, scope: !669)
!677 = !DILocation(line: 301, column: 4, scope: !669)
!678 = !DILocation(line: 302, column: 4, scope: !669)
!679 = !DILocation(line: 304, column: 7, scope: !680)
!680 = distinct !DILexicalBlock(scope: !567, file: !1, line: 304, column: 7)
!681 = !DILocation(line: 304, column: 11, scope: !680)
!682 = !DILocation(line: 304, column: 17, scope: !680)
!683 = !DILocation(line: 304, column: 20, scope: !684)
!684 = !DILexicalBlockFile(scope: !680, file: !1, discriminator: 1)
!685 = !DILocation(line: 304, column: 26, scope: !684)
!686 = !DILocation(line: 304, column: 7, scope: !684)
!687 = !DILocation(line: 305, column: 26, scope: !688)
!688 = distinct !DILexicalBlock(scope: !680, file: !1, line: 304, column: 37)
!689 = !DILocation(line: 305, column: 32, scope: !688)
!690 = !DILocation(line: 306, column: 5, scope: !688)
!691 = !DILocation(line: 306, column: 11, scope: !688)
!692 = !DILocation(line: 305, column: 4, scope: !688)
!693 = !DILocation(line: 307, column: 4, scope: !688)
!694 = !DILocation(line: 309, column: 7, scope: !695)
!695 = distinct !DILexicalBlock(scope: !567, file: !1, line: 309, column: 7)
!696 = !DILocation(line: 309, column: 11, scope: !695)
!697 = !DILocation(line: 309, column: 7, scope: !567)
!698 = !DILocation(line: 310, column: 4, scope: !695)
!699 = !DILocation(line: 312, column: 28, scope: !567)
!700 = !DILocation(line: 312, column: 3, scope: !567)
!701 = !DILocation(line: 312, column: 9, scope: !567)
!702 = !DILocation(line: 312, column: 25, scope: !567)
!703 = !DILocation(line: 314, column: 32, scope: !567)
!704 = !DILocation(line: 314, column: 35, scope: !567)
!705 = !DILocation(line: 315, column: 7, scope: !567)
!706 = !DILocation(line: 315, column: 13, scope: !567)
!707 = !DILocation(line: 315, column: 24, scope: !567)
!708 = !DILocation(line: 315, column: 30, scope: !567)
!709 = !DILocation(line: 314, column: 9, scope: !567)
!710 = !DILocation(line: 314, column: 7, scope: !567)
!711 = !DILocation(line: 316, column: 7, scope: !712)
!712 = distinct !DILexicalBlock(scope: !567, file: !1, line: 316, column: 7)
!713 = !DILocation(line: 316, column: 11, scope: !712)
!714 = !DILocation(line: 316, column: 7, scope: !567)
!715 = !DILocation(line: 317, column: 4, scope: !712)
!716 = !DILocation(line: 318, column: 3, scope: !567)
!717 = !DILocation(line: 318, column: 9, scope: !567)
!718 = !DILocation(line: 318, column: 25, scope: !567)
!719 = !DILocation(line: 269, column: 2, scope: !720)
!720 = !DILexicalBlockFile(scope: !568, file: !1, discriminator: 1)
!721 = !DILocation(line: 320, column: 1, scope: !175)
!722 = !DILocalVariable(name: "f", arg: 1, scope: !168, file: !1, line: 353, type: !139)
!723 = !DILocation(line: 353, column: 60, scope: !168)
!724 = !DILocalVariable(name: "data", arg: 2, scope: !168, file: !1, line: 354, type: !9)
!725 = !DILocation(line: 354, column: 40, scope: !168)
!726 = !DILocalVariable(name: "ret", scope: !168, file: !1, line: 356, type: !17)
!727 = !DILocation(line: 356, column: 6, scope: !168)
!728 = !DILocalVariable(name: "r1", scope: !168, file: !1, line: 356, type: !17)
!729 = !DILocation(line: 356, column: 11, scope: !168)
!730 = !DILocalVariable(name: "status", scope: !168, file: !1, line: 356, type: !17)
!731 = !DILocation(line: 356, column: 15, scope: !168)
!732 = !DILocalVariable(name: "bytes_read", scope: !168, file: !1, line: 357, type: !69)
!733 = !DILocation(line: 357, column: 10, scope: !168)
!734 = !DILocation(line: 359, column: 6, scope: !735)
!735 = distinct !DILexicalBlock(scope: !168, file: !1, line: 359, column: 6)
!736 = !DILocation(line: 359, column: 12, scope: !735)
!737 = !DILocation(line: 359, column: 18, scope: !735)
!738 = !DILocation(line: 359, column: 6, scope: !168)
!739 = !DILocation(line: 360, column: 39, scope: !735)
!740 = !DILocation(line: 360, column: 42, scope: !735)
!741 = !DILocation(line: 360, column: 10, scope: !735)
!742 = !DILocation(line: 360, column: 3, scope: !735)
!743 = !DILocation(line: 362, column: 6, scope: !168)
!744 = !DILocation(line: 363, column: 8, scope: !168)
!745 = !DILocation(line: 363, column: 14, scope: !168)
!746 = !DILocation(line: 363, column: 2, scope: !168)
!747 = !DILocation(line: 364, column: 2, scope: !168)
!748 = !DILocation(line: 364, column: 8, scope: !168)
!749 = !DILocation(line: 364, column: 20, scope: !168)
!750 = !DILocation(line: 365, column: 8, scope: !168)
!751 = !DILocation(line: 365, column: 14, scope: !168)
!752 = !DILocation(line: 365, column: 2, scope: !168)
!753 = !DILocation(line: 367, column: 2, scope: !168)
!754 = !DILocation(line: 368, column: 3, scope: !755)
!755 = distinct !DILexicalBlock(scope: !756, file: !1, line: 367, column: 11)
!756 = distinct !DILexicalBlock(scope: !757, file: !1, line: 367, column: 2)
!757 = distinct !DILexicalBlock(scope: !168, file: !1, line: 367, column: 2)
!758 = !DILocation(line: 369, column: 22, scope: !759)
!759 = distinct !DILexicalBlock(scope: !755, file: !1, line: 368, column: 6)
!760 = !DILocation(line: 369, column: 28, scope: !759)
!761 = !DILocation(line: 370, column: 8, scope: !759)
!762 = !DILocation(line: 370, column: 14, scope: !759)
!763 = !DILocation(line: 370, column: 26, scope: !759)
!764 = !DILocation(line: 370, column: 32, scope: !759)
!765 = !DILocation(line: 370, column: 24, scope: !759)
!766 = !DILocation(line: 371, column: 8, scope: !759)
!767 = !DILocation(line: 371, column: 14, scope: !759)
!768 = !DILocation(line: 371, column: 30, scope: !759)
!769 = !DILocation(line: 371, column: 36, scope: !759)
!770 = !DILocation(line: 371, column: 28, scope: !759)
!771 = !DILocation(line: 369, column: 17, scope: !759)
!772 = !DILocation(line: 369, column: 15, scope: !759)
!773 = !DILocation(line: 372, column: 3, scope: !759)
!774 = !DILocation(line: 372, column: 12, scope: !775)
!775 = !DILexicalBlockFile(scope: !755, file: !1, discriminator: 1)
!776 = !DILocation(line: 372, column: 23, scope: !775)
!777 = !DILocation(line: 372, column: 29, scope: !775)
!778 = !DILocation(line: 372, column: 32, scope: !779)
!779 = !DILexicalBlockFile(scope: !755, file: !1, discriminator: 2)
!780 = !DILocation(line: 372, column: 38, scope: !779)
!781 = !DILocation(line: 372, column: 3, scope: !782)
!782 = !DILexicalBlockFile(scope: !759, file: !1, discriminator: 3)
!783 = !DILocation(line: 374, column: 7, scope: !784)
!784 = distinct !DILexicalBlock(scope: !755, file: !1, line: 374, column: 7)
!785 = !DILocation(line: 374, column: 18, scope: !784)
!786 = !DILocation(line: 374, column: 23, scope: !784)
!787 = !DILocation(line: 374, column: 27, scope: !788)
!788 = !DILexicalBlockFile(scope: !784, file: !1, discriminator: 1)
!789 = !DILocation(line: 374, column: 38, scope: !788)
!790 = !DILocation(line: 374, column: 44, scope: !788)
!791 = !DILocation(line: 374, column: 47, scope: !792)
!792 = !DILexicalBlockFile(scope: !784, file: !1, discriminator: 2)
!793 = !DILocation(line: 374, column: 53, scope: !792)
!794 = !DILocation(line: 374, column: 7, scope: !792)
!795 = !DILocation(line: 375, column: 4, scope: !784)
!796 = !DILocation(line: 377, column: 7, scope: !797)
!797 = distinct !DILexicalBlock(scope: !755, file: !1, line: 377, column: 7)
!798 = !DILocation(line: 377, column: 18, scope: !797)
!799 = !DILocation(line: 377, column: 7, scope: !755)
!800 = !DILocation(line: 378, column: 22, scope: !801)
!801 = distinct !DILexicalBlock(scope: !797, file: !1, line: 377, column: 25)
!802 = !DILocation(line: 378, column: 25, scope: !801)
!803 = !DILocation(line: 378, column: 34, scope: !801)
!804 = !DILocation(line: 379, column: 42, scope: !801)
!805 = !DILocation(line: 379, column: 48, scope: !801)
!806 = !DILocation(line: 378, column: 4, scope: !807)
!807 = !DILexicalBlockFile(scope: !801, file: !1, discriminator: 1)
!808 = !DILocation(line: 380, column: 8, scope: !801)
!809 = !DILocation(line: 381, column: 4, scope: !801)
!810 = !DILocation(line: 383, column: 28, scope: !755)
!811 = !DILocation(line: 383, column: 3, scope: !755)
!812 = !DILocation(line: 383, column: 9, scope: !755)
!813 = !DILocation(line: 383, column: 25, scope: !755)
!814 = !DILocation(line: 385, column: 32, scope: !755)
!815 = !DILocation(line: 385, column: 35, scope: !755)
!816 = !DILocation(line: 386, column: 7, scope: !755)
!817 = !DILocation(line: 386, column: 13, scope: !755)
!818 = !DILocation(line: 386, column: 24, scope: !755)
!819 = !DILocation(line: 386, column: 30, scope: !755)
!820 = !DILocation(line: 385, column: 9, scope: !755)
!821 = !DILocation(line: 385, column: 7, scope: !755)
!822 = !DILocation(line: 387, column: 7, scope: !823)
!823 = distinct !DILexicalBlock(scope: !755, file: !1, line: 387, column: 7)
!824 = !DILocation(line: 387, column: 11, scope: !823)
!825 = !DILocation(line: 387, column: 7, scope: !755)
!826 = !DILocation(line: 388, column: 8, scope: !827)
!827 = distinct !DILexicalBlock(scope: !823, file: !1, line: 387, column: 26)
!828 = !DILocation(line: 389, column: 4, scope: !827)
!829 = !DILocation(line: 391, column: 3, scope: !755)
!830 = !DILocation(line: 391, column: 9, scope: !755)
!831 = !DILocation(line: 391, column: 25, scope: !755)
!832 = !DILocation(line: 367, column: 2, scope: !833)
!833 = !DILexicalBlockFile(scope: !756, file: !1, discriminator: 1)
!834 = !DILocation(line: 392, column: 2, scope: !757)
!835 = !DILocation(line: 396, column: 6, scope: !836)
!836 = distinct !DILexicalBlock(scope: !168, file: !1, line: 396, column: 6)
!837 = !DILocation(line: 396, column: 12, scope: !836)
!838 = !DILocation(line: 396, column: 24, scope: !836)
!839 = !DILocation(line: 396, column: 6, scope: !168)
!840 = !DILocation(line: 397, column: 9, scope: !836)
!841 = !DILocation(line: 397, column: 15, scope: !836)
!842 = !DILocation(line: 397, column: 3, scope: !836)
!843 = !DILocation(line: 398, column: 6, scope: !844)
!844 = distinct !DILexicalBlock(scope: !168, file: !1, line: 398, column: 6)
!845 = !DILocation(line: 398, column: 12, scope: !844)
!846 = !DILocation(line: 398, column: 25, scope: !844)
!847 = !DILocation(line: 398, column: 6, scope: !168)
!848 = !DILocation(line: 399, column: 9, scope: !844)
!849 = !DILocation(line: 399, column: 15, scope: !844)
!850 = !DILocation(line: 399, column: 3, scope: !844)
!851 = !DILocation(line: 400, column: 2, scope: !168)
!852 = !DILocation(line: 400, column: 17, scope: !853)
!853 = !DILexicalBlockFile(scope: !168, file: !1, discriminator: 1)
!854 = !DILocation(line: 400, column: 23, scope: !853)
!855 = !DILocation(line: 400, column: 9, scope: !853)
!856 = !DILocation(line: 400, column: 42, scope: !853)
!857 = !DILocation(line: 400, column: 48, scope: !853)
!858 = !DILocation(line: 400, column: 51, scope: !859)
!859 = !DILexicalBlockFile(scope: !168, file: !1, discriminator: 2)
!860 = !DILocation(line: 400, column: 57, scope: !859)
!861 = !DILocation(line: 400, column: 2, scope: !862)
!862 = !DILexicalBlockFile(scope: !168, file: !1, discriminator: 3)
!863 = !DILocation(line: 401, column: 3, scope: !168)
!864 = !DILocation(line: 405, column: 2, scope: !168)
!865 = !DILocation(line: 405, column: 8, scope: !168)
!866 = !DILocation(line: 405, column: 14, scope: !168)
!867 = !DILocation(line: 407, column: 6, scope: !868)
!868 = distinct !DILexicalBlock(scope: !168, file: !1, line: 407, column: 6)
!869 = !DILocation(line: 407, column: 13, scope: !868)
!870 = !DILocation(line: 407, column: 6, scope: !168)
!871 = !DILocation(line: 408, column: 21, scope: !872)
!872 = distinct !DILexicalBlock(scope: !868, file: !1, line: 407, column: 19)
!873 = !DILocation(line: 408, column: 24, scope: !872)
!874 = !DILocation(line: 409, column: 36, scope: !872)
!875 = !DILocation(line: 409, column: 42, scope: !872)
!876 = !DILocation(line: 408, column: 3, scope: !872)
!877 = !DILocation(line: 410, column: 7, scope: !872)
!878 = !DILocation(line: 411, column: 2, scope: !872)
!879 = !DILocation(line: 412, column: 36, scope: !168)
!880 = !DILocation(line: 412, column: 39, scope: !168)
!881 = !DILocation(line: 412, column: 7, scope: !168)
!882 = !DILocation(line: 412, column: 5, scope: !168)
!883 = !DILocation(line: 413, column: 10, scope: !168)
!884 = !DILocation(line: 413, column: 15, scope: !168)
!885 = !DILocation(line: 413, column: 13, scope: !168)
!886 = !DILocation(line: 413, column: 21, scope: !853)
!887 = !DILocation(line: 413, column: 10, scope: !853)
!888 = !DILocation(line: 413, column: 26, scope: !859)
!889 = !DILocation(line: 413, column: 10, scope: !859)
!890 = !DILocation(line: 413, column: 10, scope: !862)
!891 = !DILocation(line: 413, column: 2, scope: !862)
!892 = !DILocation(line: 414, column: 1, scope: !168)
