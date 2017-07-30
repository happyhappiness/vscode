; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcompress/cmcompress.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.cmcompress_stream = type { i32, i32, i64, i64, [69001 x i64], [69001 x i16], i64, i64, i32, i32, i32, i64, i64, i32, i64, i64, i64, i64, i64, i32, i64, i32, i32 (i8*)*, i32 (i8*, i8*, i32)*, i8* }

@lmask = global [9 x i8] c"\FF\FE\FC\F8\F0\E0\C0\80\00", align 1
@rmask = global [9 x i8] c"\00\01\03\07\0F\1F?\7F\FF", align 1
@magic_header = internal constant [3 x i8] c"\1F\9D\00", align 1
@stdout = external global %struct._IO_FILE*, align 8
@.str = private unnamed_addr constant [10 x i8] c"Error...\0A\00", align 1
@buf = internal global [16 x i8] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define i32 @cmcompress_compress_initialize(%struct.cmcompress_stream* %cdata) #0 !dbg !16 {
entry:
  %cdata.addr = alloca %struct.cmcompress_stream*, align 8
  store %struct.cmcompress_stream* %cdata, %struct.cmcompress_stream** %cdata.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cmcompress_stream** %cdata.addr, metadata !92, metadata !93), !dbg !94
  %0 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !95
  %maxbits = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %0, i32 0, i32 1, !dbg !96
  store i32 16, i32* %maxbits, align 4, !dbg !97
  %1 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !98
  %maxmaxcode = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %1, i32 0, i32 3, !dbg !99
  store i64 65536, i64* %maxmaxcode, align 8, !dbg !100
  %2 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !101
  %hsize = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %2, i32 0, i32 6, !dbg !102
  store i64 69001, i64* %hsize, align 8, !dbg !103
  %3 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !104
  %free_ent = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %3, i32 0, i32 7, !dbg !105
  store i64 0, i64* %free_ent, align 8, !dbg !106
  %4 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !107
  %nomagic = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %4, i32 0, i32 8, !dbg !108
  store i32 0, i32* %nomagic, align 8, !dbg !109
  %5 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !110
  %block_compress = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %5, i32 0, i32 9, !dbg !111
  store i32 128, i32* %block_compress, align 4, !dbg !112
  %6 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !113
  %clear_flg = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %6, i32 0, i32 10, !dbg !114
  store i32 0, i32* %clear_flg, align 8, !dbg !115
  %7 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !116
  %ratio = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %7, i32 0, i32 11, !dbg !117
  store i64 0, i64* %ratio, align 8, !dbg !118
  %8 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !119
  %checkpoint = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %8, i32 0, i32 12, !dbg !120
  store i64 10000, i64* %checkpoint, align 8, !dbg !121
  %9 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !122
  %input_stream = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %9, i32 0, i32 22, !dbg !123
  store i32 (i8*)* null, i32 (i8*)** %input_stream, align 8, !dbg !124
  %10 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !125
  %output_stream = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %10, i32 0, i32 23, !dbg !126
  store i32 (i8*, i8*, i32)* null, i32 (i8*, i8*, i32)** %output_stream, align 8, !dbg !127
  %11 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !128
  %client_data = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %11, i32 0, i32 24, !dbg !129
  store i8* null, i8** %client_data, align 8, !dbg !130
  ret i32 1, !dbg !131
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @cmcompress_compress_start(%struct.cmcompress_stream* %cdata) #0 !dbg !58 {
entry:
  %cdata.addr = alloca %struct.cmcompress_stream*, align 8
  %headLast = alloca i8, align 1
  store %struct.cmcompress_stream* %cdata, %struct.cmcompress_stream** %cdata.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cmcompress_stream** %cdata.addr, metadata !132, metadata !93), !dbg !133
  %0 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !134
  %nomagic = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %0, i32 0, i32 8, !dbg !136
  %1 = load i32, i32* %nomagic, align 8, !dbg !136
  %cmp = icmp eq i32 %1, 0, !dbg !137
  br i1 %cmp, label %if.then, label %if.end6, !dbg !138

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8* %headLast, metadata !139, metadata !93), !dbg !141
  %2 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !142
  %maxbits = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %2, i32 0, i32 1, !dbg !143
  %3 = load i32, i32* %maxbits, align 4, !dbg !143
  %4 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !144
  %block_compress = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %4, i32 0, i32 9, !dbg !145
  %5 = load i32, i32* %block_compress, align 4, !dbg !145
  %or = or i32 %3, %5, !dbg !146
  %conv = trunc i32 %or to i8, !dbg !147
  store i8 %conv, i8* %headLast, align 1, !dbg !141
  %6 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !148
  %output_stream = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %6, i32 0, i32 23, !dbg !149
  %7 = load i32 (i8*, i8*, i32)*, i32 (i8*, i8*, i32)** %output_stream, align 8, !dbg !149
  %8 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !150
  %9 = bitcast %struct.cmcompress_stream* %8 to i8*, !dbg !150
  %call = call i32 %7(i8* %9, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @magic_header, i32 0, i32 0), i32 2), !dbg !148
  %10 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !151
  %output_stream1 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %10, i32 0, i32 23, !dbg !152
  %11 = load i32 (i8*, i8*, i32)*, i32 (i8*, i8*, i32)** %output_stream1, align 8, !dbg !152
  %12 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !153
  %13 = bitcast %struct.cmcompress_stream* %12 to i8*, !dbg !153
  %call2 = call i32 %11(i8* %13, i8* %headLast, i32 1), !dbg !151
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !154
  %call3 = call i32 @ferror(%struct._IO_FILE* %14) #4, !dbg !156
  %tobool = icmp ne i32 %call3, 0, !dbg !156
  br i1 %tobool, label %if.then4, label %if.end, !dbg !157

if.then4:                                         ; preds = %if.then
  %call5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)), !dbg !158
  br label %if.end, !dbg !160

if.end:                                           ; preds = %if.then4, %if.then
  br label %if.end6, !dbg !161

if.end6:                                          ; preds = %if.end, %entry
  %15 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !162
  %offset = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %15, i32 0, i32 13, !dbg !163
  store i32 0, i32* %offset, align 8, !dbg !164
  %16 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !165
  %bytes_out = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %16, i32 0, i32 15, !dbg !166
  store i64 3, i64* %bytes_out, align 8, !dbg !167
  %17 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !168
  %out_count = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %17, i32 0, i32 16, !dbg !169
  store i64 0, i64* %out_count, align 8, !dbg !170
  %18 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !171
  %clear_flg = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %18, i32 0, i32 10, !dbg !172
  store i32 0, i32* %clear_flg, align 8, !dbg !173
  %19 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !174
  %ratio = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %19, i32 0, i32 11, !dbg !175
  store i64 0, i64* %ratio, align 8, !dbg !176
  %20 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !177
  %in_count = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %20, i32 0, i32 14, !dbg !178
  store i64 1, i64* %in_count, align 8, !dbg !179
  %21 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !180
  %checkpoint = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %21, i32 0, i32 12, !dbg !181
  store i64 10000, i64* %checkpoint, align 8, !dbg !182
  %22 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !183
  %n_bits = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %22, i32 0, i32 0, !dbg !183
  store i32 9, i32* %n_bits, align 8, !dbg !183
  %23 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !184
  %maxcode = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %23, i32 0, i32 2, !dbg !185
  store i64 511, i64* %maxcode, align 8, !dbg !186
  %24 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !187
  %block_compress7 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %24, i32 0, i32 9, !dbg !188
  %25 = load i32, i32* %block_compress7, align 4, !dbg !188
  %tobool8 = icmp ne i32 %25, 0, !dbg !189
  %cond = select i1 %tobool8, i32 257, i32 256, !dbg !189
  %conv9 = sext i32 %cond to i64, !dbg !190
  %26 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !191
  %free_ent = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %26, i32 0, i32 7, !dbg !192
  store i64 %conv9, i64* %free_ent, align 8, !dbg !193
  %27 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !194
  %first_pass = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %27, i32 0, i32 21, !dbg !195
  store i32 1, i32* %first_pass, align 8, !dbg !196
  %28 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !197
  %hshift = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %28, i32 0, i32 19, !dbg !198
  store i32 0, i32* %hshift, align 8, !dbg !199
  %29 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !200
  %hsize = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %29, i32 0, i32 6, !dbg !202
  %30 = load i64, i64* %hsize, align 8, !dbg !202
  %31 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !203
  %fcode = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %31, i32 0, i32 20, !dbg !204
  store i64 %30, i64* %fcode, align 8, !dbg !205
  br label %for.cond, !dbg !203

for.cond:                                         ; preds = %for.inc, %if.end6
  %32 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !206
  %fcode10 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %32, i32 0, i32 20, !dbg !209
  %33 = load i64, i64* %fcode10, align 8, !dbg !209
  %cmp11 = icmp slt i64 %33, 65536, !dbg !210
  br i1 %cmp11, label %for.body, label %for.end, !dbg !211

for.body:                                         ; preds = %for.cond
  %34 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !212
  %hshift13 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %34, i32 0, i32 19, !dbg !214
  %35 = load i32, i32* %hshift13, align 8, !dbg !215
  %inc = add nsw i32 %35, 1, !dbg !215
  store i32 %inc, i32* %hshift13, align 8, !dbg !215
  br label %for.inc, !dbg !216

for.inc:                                          ; preds = %for.body
  %36 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !217
  %fcode14 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %36, i32 0, i32 20, !dbg !219
  %37 = load i64, i64* %fcode14, align 8, !dbg !220
  %mul = mul nsw i64 %37, 2, !dbg !220
  store i64 %mul, i64* %fcode14, align 8, !dbg !220
  br label %for.cond, !dbg !221

for.end:                                          ; preds = %for.cond
  %38 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !222
  %hshift15 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %38, i32 0, i32 19, !dbg !223
  %39 = load i32, i32* %hshift15, align 8, !dbg !223
  %sub = sub nsw i32 8, %39, !dbg !224
  %40 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !225
  %hshift16 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %40, i32 0, i32 19, !dbg !226
  store i32 %sub, i32* %hshift16, align 8, !dbg !227
  %41 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !228
  %hsize17 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %41, i32 0, i32 6, !dbg !229
  %42 = load i64, i64* %hsize17, align 8, !dbg !229
  %43 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !230
  %hsize_reg = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %43, i32 0, i32 18, !dbg !231
  store i64 %42, i64* %hsize_reg, align 8, !dbg !232
  %44 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !233
  %45 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !234
  %hsize_reg18 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %45, i32 0, i32 18, !dbg !235
  %46 = load i64, i64* %hsize_reg18, align 8, !dbg !235
  call void @cl_hash(%struct.cmcompress_stream* %44, i64 %46), !dbg !236
  ret i32 1, !dbg !237
}

; Function Attrs: nounwind
declare i32 @ferror(%struct._IO_FILE*) #2

declare i32 @printf(i8*, ...) #3

; Function Attrs: nounwind uwtable
define internal void @cl_hash(%struct.cmcompress_stream* %cdata, i64 %hsize) #0 !dbg !66 {
entry:
  %cdata.addr = alloca %struct.cmcompress_stream*, align 8
  %hsize.addr = alloca i64, align 8
  %htab_p = alloca i64*, align 8
  %i = alloca i64, align 8
  %m1 = alloca i64, align 8
  store %struct.cmcompress_stream* %cdata, %struct.cmcompress_stream** %cdata.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cmcompress_stream** %cdata.addr, metadata !238, metadata !93), !dbg !239
  store i64 %hsize, i64* %hsize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %hsize.addr, metadata !240, metadata !93), !dbg !241
  call void @llvm.dbg.declare(metadata i64** %htab_p, metadata !242, metadata !93), !dbg !244
  %0 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !245
  %htab = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %0, i32 0, i32 4, !dbg !246
  %arraydecay = getelementptr inbounds [69001 x i64], [69001 x i64]* %htab, i32 0, i32 0, !dbg !245
  %1 = load i64, i64* %hsize.addr, align 8, !dbg !247
  %add.ptr = getelementptr inbounds i64, i64* %arraydecay, i64 %1, !dbg !248
  store i64* %add.ptr, i64** %htab_p, align 8, !dbg !244
  call void @llvm.dbg.declare(metadata i64* %i, metadata !249, metadata !93), !dbg !250
  call void @llvm.dbg.declare(metadata i64* %m1, metadata !251, metadata !93), !dbg !252
  store i64 -1, i64* %m1, align 8, !dbg !252
  %2 = load i64, i64* %hsize.addr, align 8, !dbg !253
  %sub = sub nsw i64 %2, 16, !dbg !254
  store i64 %sub, i64* %i, align 8, !dbg !255
  br label %do.body, !dbg !256

do.body:                                          ; preds = %do.cond, %entry
  %3 = load i64, i64* %m1, align 8, !dbg !257
  %4 = load i64*, i64** %htab_p, align 8, !dbg !259
  %add.ptr1 = getelementptr inbounds i64, i64* %4, i64 -16, !dbg !260
  store i64 %3, i64* %add.ptr1, align 8, !dbg !261
  %5 = load i64, i64* %m1, align 8, !dbg !262
  %6 = load i64*, i64** %htab_p, align 8, !dbg !263
  %add.ptr2 = getelementptr inbounds i64, i64* %6, i64 -15, !dbg !264
  store i64 %5, i64* %add.ptr2, align 8, !dbg !265
  %7 = load i64, i64* %m1, align 8, !dbg !266
  %8 = load i64*, i64** %htab_p, align 8, !dbg !267
  %add.ptr3 = getelementptr inbounds i64, i64* %8, i64 -14, !dbg !268
  store i64 %7, i64* %add.ptr3, align 8, !dbg !269
  %9 = load i64, i64* %m1, align 8, !dbg !270
  %10 = load i64*, i64** %htab_p, align 8, !dbg !271
  %add.ptr4 = getelementptr inbounds i64, i64* %10, i64 -13, !dbg !272
  store i64 %9, i64* %add.ptr4, align 8, !dbg !273
  %11 = load i64, i64* %m1, align 8, !dbg !274
  %12 = load i64*, i64** %htab_p, align 8, !dbg !275
  %add.ptr5 = getelementptr inbounds i64, i64* %12, i64 -12, !dbg !276
  store i64 %11, i64* %add.ptr5, align 8, !dbg !277
  %13 = load i64, i64* %m1, align 8, !dbg !278
  %14 = load i64*, i64** %htab_p, align 8, !dbg !279
  %add.ptr6 = getelementptr inbounds i64, i64* %14, i64 -11, !dbg !280
  store i64 %13, i64* %add.ptr6, align 8, !dbg !281
  %15 = load i64, i64* %m1, align 8, !dbg !282
  %16 = load i64*, i64** %htab_p, align 8, !dbg !283
  %add.ptr7 = getelementptr inbounds i64, i64* %16, i64 -10, !dbg !284
  store i64 %15, i64* %add.ptr7, align 8, !dbg !285
  %17 = load i64, i64* %m1, align 8, !dbg !286
  %18 = load i64*, i64** %htab_p, align 8, !dbg !287
  %add.ptr8 = getelementptr inbounds i64, i64* %18, i64 -9, !dbg !288
  store i64 %17, i64* %add.ptr8, align 8, !dbg !289
  %19 = load i64, i64* %m1, align 8, !dbg !290
  %20 = load i64*, i64** %htab_p, align 8, !dbg !291
  %add.ptr9 = getelementptr inbounds i64, i64* %20, i64 -8, !dbg !292
  store i64 %19, i64* %add.ptr9, align 8, !dbg !293
  %21 = load i64, i64* %m1, align 8, !dbg !294
  %22 = load i64*, i64** %htab_p, align 8, !dbg !295
  %add.ptr10 = getelementptr inbounds i64, i64* %22, i64 -7, !dbg !296
  store i64 %21, i64* %add.ptr10, align 8, !dbg !297
  %23 = load i64, i64* %m1, align 8, !dbg !298
  %24 = load i64*, i64** %htab_p, align 8, !dbg !299
  %add.ptr11 = getelementptr inbounds i64, i64* %24, i64 -6, !dbg !300
  store i64 %23, i64* %add.ptr11, align 8, !dbg !301
  %25 = load i64, i64* %m1, align 8, !dbg !302
  %26 = load i64*, i64** %htab_p, align 8, !dbg !303
  %add.ptr12 = getelementptr inbounds i64, i64* %26, i64 -5, !dbg !304
  store i64 %25, i64* %add.ptr12, align 8, !dbg !305
  %27 = load i64, i64* %m1, align 8, !dbg !306
  %28 = load i64*, i64** %htab_p, align 8, !dbg !307
  %add.ptr13 = getelementptr inbounds i64, i64* %28, i64 -4, !dbg !308
  store i64 %27, i64* %add.ptr13, align 8, !dbg !309
  %29 = load i64, i64* %m1, align 8, !dbg !310
  %30 = load i64*, i64** %htab_p, align 8, !dbg !311
  %add.ptr14 = getelementptr inbounds i64, i64* %30, i64 -3, !dbg !312
  store i64 %29, i64* %add.ptr14, align 8, !dbg !313
  %31 = load i64, i64* %m1, align 8, !dbg !314
  %32 = load i64*, i64** %htab_p, align 8, !dbg !315
  %add.ptr15 = getelementptr inbounds i64, i64* %32, i64 -2, !dbg !316
  store i64 %31, i64* %add.ptr15, align 8, !dbg !317
  %33 = load i64, i64* %m1, align 8, !dbg !318
  %34 = load i64*, i64** %htab_p, align 8, !dbg !319
  %add.ptr16 = getelementptr inbounds i64, i64* %34, i64 -1, !dbg !320
  store i64 %33, i64* %add.ptr16, align 8, !dbg !321
  %35 = load i64*, i64** %htab_p, align 8, !dbg !322
  %add.ptr17 = getelementptr inbounds i64, i64* %35, i64 -16, !dbg !322
  store i64* %add.ptr17, i64** %htab_p, align 8, !dbg !322
  br label %do.cond, !dbg !323

do.cond:                                          ; preds = %do.body
  %36 = load i64, i64* %i, align 8, !dbg !324
  %sub18 = sub nsw i64 %36, 16, !dbg !324
  store i64 %sub18, i64* %i, align 8, !dbg !324
  %cmp = icmp sge i64 %sub18, 0, !dbg !325
  br i1 %cmp, label %do.body, label %do.end, !dbg !326

do.end:                                           ; preds = %do.cond
  %37 = load i64, i64* %i, align 8, !dbg !328
  %add = add nsw i64 %37, 16, !dbg !328
  store i64 %add, i64* %i, align 8, !dbg !328
  br label %for.cond, !dbg !330

for.cond:                                         ; preds = %for.inc, %do.end
  %38 = load i64, i64* %i, align 8, !dbg !331
  %cmp19 = icmp sgt i64 %38, 0, !dbg !334
  br i1 %cmp19, label %for.body, label %for.end, !dbg !335

for.body:                                         ; preds = %for.cond
  %39 = load i64, i64* %m1, align 8, !dbg !336
  %40 = load i64*, i64** %htab_p, align 8, !dbg !338
  %incdec.ptr = getelementptr inbounds i64, i64* %40, i32 -1, !dbg !338
  store i64* %incdec.ptr, i64** %htab_p, align 8, !dbg !338
  store i64 %39, i64* %incdec.ptr, align 8, !dbg !339
  br label %for.inc, !dbg !340

for.inc:                                          ; preds = %for.body
  %41 = load i64, i64* %i, align 8, !dbg !341
  %dec = add nsw i64 %41, -1, !dbg !341
  store i64 %dec, i64* %i, align 8, !dbg !341
  br label %for.cond, !dbg !343

for.end:                                          ; preds = %for.cond
  ret void, !dbg !344
}

; Function Attrs: nounwind uwtable
define i32 @cmcompress_compress(%struct.cmcompress_stream* %cdata, i8* %buff, i64 %n) #0 !dbg !59 {
entry:
  %retval = alloca i32, align 4
  %cdata.addr = alloca %struct.cmcompress_stream*, align 8
  %buff.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  %i = alloca i64, align 8
  %c = alloca i32, align 4
  %disp = alloca i32, align 4
  %input_buffer = alloca i8*, align 8
  %cc = alloca i64, align 8
  store %struct.cmcompress_stream* %cdata, %struct.cmcompress_stream** %cdata.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cmcompress_stream** %cdata.addr, metadata !345, metadata !93), !dbg !346
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !347, metadata !93), !dbg !348
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !349, metadata !93), !dbg !350
  call void @llvm.dbg.declare(metadata i64* %i, metadata !351, metadata !93), !dbg !352
  call void @llvm.dbg.declare(metadata i32* %c, metadata !353, metadata !93), !dbg !354
  call void @llvm.dbg.declare(metadata i32* %disp, metadata !355, metadata !93), !dbg !356
  call void @llvm.dbg.declare(metadata i8** %input_buffer, metadata !357, metadata !93), !dbg !358
  %0 = load i8*, i8** %buff.addr, align 8, !dbg !359
  store i8* %0, i8** %input_buffer, align 8, !dbg !358
  call void @llvm.dbg.declare(metadata i64* %cc, metadata !360, metadata !93), !dbg !361
  %1 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !362
  %first_pass = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %1, i32 0, i32 21, !dbg !364
  %2 = load i32, i32* %first_pass, align 8, !dbg !364
  %tobool = icmp ne i32 %2, 0, !dbg !362
  br i1 %tobool, label %if.then, label %if.end, !dbg !365

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %input_buffer, align 8, !dbg !366
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 0, !dbg !366
  %4 = load i8, i8* %arrayidx, align 1, !dbg !366
  %conv = zext i8 %4 to i64, !dbg !366
  %5 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !368
  %ent = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %5, i32 0, i32 17, !dbg !369
  store i64 %conv, i64* %ent, align 8, !dbg !370
  %6 = load i8*, i8** %input_buffer, align 8, !dbg !371
  %incdec.ptr = getelementptr inbounds i8, i8* %6, i32 1, !dbg !371
  store i8* %incdec.ptr, i8** %input_buffer, align 8, !dbg !371
  %7 = load i64, i64* %n.addr, align 8, !dbg !372
  %dec = add i64 %7, -1, !dbg !372
  store i64 %dec, i64* %n.addr, align 8, !dbg !372
  %8 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !373
  %first_pass1 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %8, i32 0, i32 21, !dbg !374
  store i32 0, i32* %first_pass1, align 8, !dbg !375
  br label %if.end, !dbg !376

if.end:                                           ; preds = %if.then, %entry
  store i64 0, i64* %cc, align 8, !dbg !377
  br label %for.cond, !dbg !379

for.cond:                                         ; preds = %for.inc, %if.end
  %9 = load i64, i64* %cc, align 8, !dbg !380
  %10 = load i64, i64* %n.addr, align 8, !dbg !383
  %cmp = icmp ult i64 %9, %10, !dbg !384
  br i1 %cmp, label %for.body, label %for.end, !dbg !385

for.body:                                         ; preds = %for.cond
  %11 = load i64, i64* %cc, align 8, !dbg !386
  %12 = load i8*, i8** %input_buffer, align 8, !dbg !388
  %arrayidx3 = getelementptr inbounds i8, i8* %12, i64 %11, !dbg !388
  %13 = load i8, i8* %arrayidx3, align 1, !dbg !388
  %conv4 = zext i8 %13 to i32, !dbg !388
  store i32 %conv4, i32* %c, align 4, !dbg !389
  %14 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !390
  %in_count = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %14, i32 0, i32 14, !dbg !391
  %15 = load i64, i64* %in_count, align 8, !dbg !392
  %inc = add nsw i64 %15, 1, !dbg !392
  store i64 %inc, i64* %in_count, align 8, !dbg !392
  %16 = load i32, i32* %c, align 4, !dbg !393
  %conv5 = sext i32 %16 to i64, !dbg !394
  %17 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !395
  %maxbits = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %17, i32 0, i32 1, !dbg !396
  %18 = load i32, i32* %maxbits, align 4, !dbg !396
  %sh_prom = zext i32 %18 to i64, !dbg !397
  %shl = shl i64 %conv5, %sh_prom, !dbg !397
  %19 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !398
  %ent6 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %19, i32 0, i32 17, !dbg !399
  %20 = load i64, i64* %ent6, align 8, !dbg !399
  %add = add nsw i64 %shl, %20, !dbg !400
  %21 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !401
  %fcode = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %21, i32 0, i32 20, !dbg !402
  store i64 %add, i64* %fcode, align 8, !dbg !403
  %22 = load i32, i32* %c, align 4, !dbg !404
  %23 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !405
  %hshift = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %23, i32 0, i32 19, !dbg !406
  %24 = load i32, i32* %hshift, align 8, !dbg !406
  %shl7 = shl i32 %22, %24, !dbg !407
  %conv8 = sext i32 %shl7 to i64, !dbg !408
  %25 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !409
  %ent9 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %25, i32 0, i32 17, !dbg !410
  %26 = load i64, i64* %ent9, align 8, !dbg !410
  %xor = xor i64 %conv8, %26, !dbg !411
  store i64 %xor, i64* %i, align 8, !dbg !412
  %27 = load i64, i64* %i, align 8, !dbg !413
  %28 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !413
  %htab = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %28, i32 0, i32 4, !dbg !413
  %arrayidx10 = getelementptr inbounds [69001 x i64], [69001 x i64]* %htab, i64 0, i64 %27, !dbg !413
  %29 = load i64, i64* %arrayidx10, align 8, !dbg !413
  %30 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !415
  %fcode11 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %30, i32 0, i32 20, !dbg !416
  %31 = load i64, i64* %fcode11, align 8, !dbg !416
  %cmp12 = icmp eq i64 %29, %31, !dbg !417
  br i1 %cmp12, label %if.then14, label %if.else, !dbg !418

if.then14:                                        ; preds = %for.body
  %32 = load i64, i64* %i, align 8, !dbg !419
  %33 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !419
  %codetab = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %33, i32 0, i32 5, !dbg !419
  %arrayidx15 = getelementptr inbounds [69001 x i16], [69001 x i16]* %codetab, i64 0, i64 %32, !dbg !419
  %34 = load i16, i16* %arrayidx15, align 2, !dbg !419
  %conv16 = zext i16 %34 to i64, !dbg !419
  %35 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !421
  %ent17 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %35, i32 0, i32 17, !dbg !422
  store i64 %conv16, i64* %ent17, align 8, !dbg !423
  br label %for.inc, !dbg !424

if.else:                                          ; preds = %for.body
  %36 = load i64, i64* %i, align 8, !dbg !425
  %37 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !425
  %htab18 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %37, i32 0, i32 4, !dbg !425
  %arrayidx19 = getelementptr inbounds [69001 x i64], [69001 x i64]* %htab18, i64 0, i64 %36, !dbg !425
  %38 = load i64, i64* %arrayidx19, align 8, !dbg !425
  %cmp20 = icmp slt i64 %38, 0, !dbg !427
  br i1 %cmp20, label %if.then22, label %if.end23, !dbg !428

if.then22:                                        ; preds = %if.else
  br label %nomatch, !dbg !429

if.end23:                                         ; preds = %if.else
  br label %if.end24

if.end24:                                         ; preds = %if.end23
  %39 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !431
  %hsize_reg = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %39, i32 0, i32 18, !dbg !432
  %40 = load i64, i64* %hsize_reg, align 8, !dbg !432
  %41 = load i64, i64* %i, align 8, !dbg !433
  %sub = sub nsw i64 %40, %41, !dbg !434
  %conv25 = trunc i64 %sub to i32, !dbg !435
  store i32 %conv25, i32* %disp, align 4, !dbg !436
  %42 = load i64, i64* %i, align 8, !dbg !437
  %cmp26 = icmp eq i64 %42, 0, !dbg !439
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !440

if.then28:                                        ; preds = %if.end24
  store i32 1, i32* %disp, align 4, !dbg !441
  br label %if.end29, !dbg !443

if.end29:                                         ; preds = %if.then28, %if.end24
  br label %probe, !dbg !444

probe:                                            ; preds = %if.then53, %if.end29
  %43 = load i32, i32* %disp, align 4, !dbg !446
  %conv30 = sext i32 %43 to i64, !dbg !446
  %44 = load i64, i64* %i, align 8, !dbg !448
  %sub31 = sub nsw i64 %44, %conv30, !dbg !448
  store i64 %sub31, i64* %i, align 8, !dbg !448
  %cmp32 = icmp slt i64 %sub31, 0, !dbg !449
  br i1 %cmp32, label %if.then34, label %if.end37, !dbg !450

if.then34:                                        ; preds = %probe
  %45 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !451
  %hsize_reg35 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %45, i32 0, i32 18, !dbg !453
  %46 = load i64, i64* %hsize_reg35, align 8, !dbg !453
  %47 = load i64, i64* %i, align 8, !dbg !454
  %add36 = add nsw i64 %47, %46, !dbg !454
  store i64 %add36, i64* %i, align 8, !dbg !454
  br label %if.end37, !dbg !455

if.end37:                                         ; preds = %if.then34, %probe
  %48 = load i64, i64* %i, align 8, !dbg !456
  %49 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !456
  %htab38 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %49, i32 0, i32 4, !dbg !456
  %arrayidx39 = getelementptr inbounds [69001 x i64], [69001 x i64]* %htab38, i64 0, i64 %48, !dbg !456
  %50 = load i64, i64* %arrayidx39, align 8, !dbg !456
  %51 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !458
  %fcode40 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %51, i32 0, i32 20, !dbg !459
  %52 = load i64, i64* %fcode40, align 8, !dbg !459
  %cmp41 = icmp eq i64 %50, %52, !dbg !460
  br i1 %cmp41, label %if.then43, label %if.end48, !dbg !461

if.then43:                                        ; preds = %if.end37
  %53 = load i64, i64* %i, align 8, !dbg !462
  %54 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !462
  %codetab44 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %54, i32 0, i32 5, !dbg !462
  %arrayidx45 = getelementptr inbounds [69001 x i16], [69001 x i16]* %codetab44, i64 0, i64 %53, !dbg !462
  %55 = load i16, i16* %arrayidx45, align 2, !dbg !462
  %conv46 = zext i16 %55 to i64, !dbg !462
  %56 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !464
  %ent47 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %56, i32 0, i32 17, !dbg !465
  store i64 %conv46, i64* %ent47, align 8, !dbg !466
  br label %for.inc, !dbg !467

if.end48:                                         ; preds = %if.end37
  %57 = load i64, i64* %i, align 8, !dbg !468
  %58 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !468
  %htab49 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %58, i32 0, i32 4, !dbg !468
  %arrayidx50 = getelementptr inbounds [69001 x i64], [69001 x i64]* %htab49, i64 0, i64 %57, !dbg !468
  %59 = load i64, i64* %arrayidx50, align 8, !dbg !468
  %cmp51 = icmp sgt i64 %59, 0, !dbg !470
  br i1 %cmp51, label %if.then53, label %if.end54, !dbg !471

if.then53:                                        ; preds = %if.end48
  br label %probe, !dbg !472

if.end54:                                         ; preds = %if.end48
  br label %nomatch, !dbg !474

nomatch:                                          ; preds = %if.end54, %if.then22
  %60 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !476
  %61 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !478
  %ent55 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %61, i32 0, i32 17, !dbg !479
  %62 = load i64, i64* %ent55, align 8, !dbg !479
  %call = call i32 @output(%struct.cmcompress_stream* %60, i64 %62), !dbg !480
  %tobool56 = icmp ne i32 %call, 0, !dbg !480
  br i1 %tobool56, label %if.end58, label %if.then57, !dbg !481

if.then57:                                        ; preds = %nomatch
  store i32 0, i32* %retval, align 4, !dbg !482
  br label %return, !dbg !482

if.end58:                                         ; preds = %nomatch
  %63 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !484
  %out_count = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %63, i32 0, i32 16, !dbg !485
  %64 = load i64, i64* %out_count, align 8, !dbg !486
  %inc59 = add nsw i64 %64, 1, !dbg !486
  store i64 %inc59, i64* %out_count, align 8, !dbg !486
  %65 = load i32, i32* %c, align 4, !dbg !487
  %conv60 = sext i32 %65 to i64, !dbg !487
  %66 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !488
  %ent61 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %66, i32 0, i32 17, !dbg !489
  store i64 %conv60, i64* %ent61, align 8, !dbg !490
  %67 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !491
  %free_ent = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %67, i32 0, i32 7, !dbg !493
  %68 = load i64, i64* %free_ent, align 8, !dbg !493
  %69 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !494
  %maxmaxcode = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %69, i32 0, i32 3, !dbg !495
  %70 = load i64, i64* %maxmaxcode, align 8, !dbg !495
  %cmp62 = icmp slt i64 %68, %70, !dbg !496
  br i1 %cmp62, label %if.then64, label %if.else73, !dbg !497

if.then64:                                        ; preds = %if.end58
  %71 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !498
  %free_ent65 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %71, i32 0, i32 7, !dbg !500
  %72 = load i64, i64* %free_ent65, align 8, !dbg !501
  %inc66 = add nsw i64 %72, 1, !dbg !501
  store i64 %inc66, i64* %free_ent65, align 8, !dbg !501
  %conv67 = trunc i64 %72 to i16, !dbg !502
  %73 = load i64, i64* %i, align 8, !dbg !503
  %74 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !503
  %codetab68 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %74, i32 0, i32 5, !dbg !503
  %arrayidx69 = getelementptr inbounds [69001 x i16], [69001 x i16]* %codetab68, i64 0, i64 %73, !dbg !503
  store i16 %conv67, i16* %arrayidx69, align 2, !dbg !504
  %75 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !505
  %fcode70 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %75, i32 0, i32 20, !dbg !506
  %76 = load i64, i64* %fcode70, align 8, !dbg !506
  %77 = load i64, i64* %i, align 8, !dbg !507
  %78 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !507
  %htab71 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %78, i32 0, i32 4, !dbg !507
  %arrayidx72 = getelementptr inbounds [69001 x i64], [69001 x i64]* %htab71, i64 0, i64 %77, !dbg !507
  store i64 %76, i64* %arrayidx72, align 8, !dbg !508
  br label %if.end84, !dbg !509

if.else73:                                        ; preds = %if.end58
  %79 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !510
  %in_count74 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %79, i32 0, i32 14, !dbg !512
  %80 = load i64, i64* %in_count74, align 8, !dbg !512
  %81 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !513
  %checkpoint = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %81, i32 0, i32 12, !dbg !514
  %82 = load i64, i64* %checkpoint, align 8, !dbg !514
  %cmp75 = icmp sge i64 %80, %82, !dbg !515
  br i1 %cmp75, label %land.lhs.true, label %if.end83, !dbg !516

land.lhs.true:                                    ; preds = %if.else73
  %83 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !517
  %block_compress = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %83, i32 0, i32 9, !dbg !519
  %84 = load i32, i32* %block_compress, align 4, !dbg !519
  %tobool77 = icmp ne i32 %84, 0, !dbg !517
  br i1 %tobool77, label %if.then78, label %if.end83, !dbg !520

if.then78:                                        ; preds = %land.lhs.true
  %85 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !521
  %call79 = call i32 @cl_block(%struct.cmcompress_stream* %85), !dbg !524
  %tobool80 = icmp ne i32 %call79, 0, !dbg !524
  br i1 %tobool80, label %if.end82, label %if.then81, !dbg !525

if.then81:                                        ; preds = %if.then78
  store i32 0, i32* %retval, align 4, !dbg !526
  br label %return, !dbg !526

if.end82:                                         ; preds = %if.then78
  br label %if.end83, !dbg !528

if.end83:                                         ; preds = %if.end82, %land.lhs.true, %if.else73
  br label %if.end84

if.end84:                                         ; preds = %if.end83, %if.then64
  br label %for.inc, !dbg !529

for.inc:                                          ; preds = %if.end84, %if.then43, %if.then14
  %86 = load i64, i64* %cc, align 8, !dbg !530
  %inc85 = add i64 %86, 1, !dbg !530
  store i64 %inc85, i64* %cc, align 8, !dbg !530
  br label %for.cond, !dbg !532

for.end:                                          ; preds = %for.cond
  store i32 1, i32* %retval, align 4, !dbg !533
  br label %return, !dbg !533

return:                                           ; preds = %for.end, %if.then81, %if.then57
  %87 = load i32, i32* %retval, align 4, !dbg !534
  ret i32 %87, !dbg !534
}

; Function Attrs: nounwind uwtable
define internal i32 @output(%struct.cmcompress_stream* %cdata, i64 %code) #0 !dbg !69 {
entry:
  %retval = alloca i32, align 4
  %cdata.addr = alloca %struct.cmcompress_stream*, align 8
  %code.addr = alloca i64, align 8
  %r_off = alloca i32, align 4
  %bits = alloca i32, align 4
  %bp = alloca i8*, align 8
  store %struct.cmcompress_stream* %cdata, %struct.cmcompress_stream** %cdata.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cmcompress_stream** %cdata.addr, metadata !535, metadata !93), !dbg !536
  store i64 %code, i64* %code.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %code.addr, metadata !537, metadata !93), !dbg !538
  call void @llvm.dbg.declare(metadata i32* %r_off, metadata !539, metadata !93), !dbg !540
  %0 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !541
  %offset = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %0, i32 0, i32 13, !dbg !542
  %1 = load i32, i32* %offset, align 8, !dbg !542
  store i32 %1, i32* %r_off, align 4, !dbg !540
  call void @llvm.dbg.declare(metadata i32* %bits, metadata !543, metadata !93), !dbg !544
  %2 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !545
  %n_bits = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %2, i32 0, i32 0, !dbg !546
  %3 = load i32, i32* %n_bits, align 8, !dbg !546
  store i32 %3, i32* %bits, align 4, !dbg !544
  call void @llvm.dbg.declare(metadata i8** %bp, metadata !547, metadata !93), !dbg !549
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @buf, i32 0, i32 0), i8** %bp, align 8, !dbg !549
  %4 = load i64, i64* %code.addr, align 8, !dbg !550
  %cmp = icmp sge i64 %4, 0, !dbg !552
  br i1 %cmp, label %if.then, label %if.else86, !dbg !553

if.then:                                          ; preds = %entry
  %5 = load i32, i32* %r_off, align 4, !dbg !554
  %shr = ashr i32 %5, 3, !dbg !556
  %6 = load i8*, i8** %bp, align 8, !dbg !557
  %idx.ext = sext i32 %shr to i64, !dbg !557
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 %idx.ext, !dbg !557
  store i8* %add.ptr, i8** %bp, align 8, !dbg !557
  %7 = load i32, i32* %r_off, align 4, !dbg !558
  %and = and i32 %7, 7, !dbg !558
  store i32 %and, i32* %r_off, align 4, !dbg !558
  %8 = load i8*, i8** %bp, align 8, !dbg !559
  %9 = load i8, i8* %8, align 1, !dbg !560
  %conv = sext i8 %9 to i32, !dbg !560
  %10 = load i32, i32* %r_off, align 4, !dbg !561
  %idxprom = sext i32 %10 to i64, !dbg !562
  %arrayidx = getelementptr inbounds [9 x i8], [9 x i8]* @rmask, i64 0, i64 %idxprom, !dbg !562
  %11 = load i8, i8* %arrayidx, align 1, !dbg !562
  %conv1 = zext i8 %11 to i32, !dbg !562
  %and2 = and i32 %conv, %conv1, !dbg !563
  %conv3 = sext i32 %and2 to i64, !dbg !564
  %12 = load i64, i64* %code.addr, align 8, !dbg !565
  %13 = load i32, i32* %r_off, align 4, !dbg !566
  %sh_prom = zext i32 %13 to i64, !dbg !567
  %shl = shl i64 %12, %sh_prom, !dbg !567
  %14 = load i32, i32* %r_off, align 4, !dbg !568
  %idxprom4 = sext i32 %14 to i64, !dbg !569
  %arrayidx5 = getelementptr inbounds [9 x i8], [9 x i8]* @lmask, i64 0, i64 %idxprom4, !dbg !569
  %15 = load i8, i8* %arrayidx5, align 1, !dbg !569
  %conv6 = zext i8 %15 to i64, !dbg !569
  %and7 = and i64 %shl, %conv6, !dbg !570
  %or = or i64 %conv3, %and7, !dbg !571
  %conv8 = trunc i64 %or to i8, !dbg !572
  %16 = load i8*, i8** %bp, align 8, !dbg !573
  store i8 %conv8, i8* %16, align 1, !dbg !574
  %17 = load i8*, i8** %bp, align 8, !dbg !575
  %incdec.ptr = getelementptr inbounds i8, i8* %17, i32 1, !dbg !575
  store i8* %incdec.ptr, i8** %bp, align 8, !dbg !575
  %18 = load i32, i32* %r_off, align 4, !dbg !576
  %sub = sub nsw i32 8, %18, !dbg !577
  %19 = load i32, i32* %bits, align 4, !dbg !578
  %sub9 = sub nsw i32 %19, %sub, !dbg !578
  store i32 %sub9, i32* %bits, align 4, !dbg !578
  %20 = load i32, i32* %r_off, align 4, !dbg !579
  %sub10 = sub nsw i32 8, %20, !dbg !580
  %21 = load i64, i64* %code.addr, align 8, !dbg !581
  %sh_prom11 = zext i32 %sub10 to i64, !dbg !581
  %shr12 = ashr i64 %21, %sh_prom11, !dbg !581
  store i64 %shr12, i64* %code.addr, align 8, !dbg !581
  %22 = load i32, i32* %bits, align 4, !dbg !582
  %cmp13 = icmp sge i32 %22, 8, !dbg !584
  br i1 %cmp13, label %if.then15, label %if.end, !dbg !585

if.then15:                                        ; preds = %if.then
  %23 = load i64, i64* %code.addr, align 8, !dbg !586
  %conv16 = trunc i64 %23 to i8, !dbg !588
  %24 = load i8*, i8** %bp, align 8, !dbg !589
  %incdec.ptr17 = getelementptr inbounds i8, i8* %24, i32 1, !dbg !589
  store i8* %incdec.ptr17, i8** %bp, align 8, !dbg !589
  store i8 %conv16, i8* %24, align 1, !dbg !590
  %25 = load i64, i64* %code.addr, align 8, !dbg !591
  %shr18 = ashr i64 %25, 8, !dbg !591
  store i64 %shr18, i64* %code.addr, align 8, !dbg !591
  %26 = load i32, i32* %bits, align 4, !dbg !592
  %sub19 = sub nsw i32 %26, 8, !dbg !592
  store i32 %sub19, i32* %bits, align 4, !dbg !592
  br label %if.end, !dbg !593

if.end:                                           ; preds = %if.then15, %if.then
  %27 = load i32, i32* %bits, align 4, !dbg !594
  %tobool = icmp ne i32 %27, 0, !dbg !594
  br i1 %tobool, label %if.then20, label %if.end22, !dbg !596

if.then20:                                        ; preds = %if.end
  %28 = load i64, i64* %code.addr, align 8, !dbg !597
  %conv21 = trunc i64 %28 to i8, !dbg !599
  %29 = load i8*, i8** %bp, align 8, !dbg !600
  store i8 %conv21, i8* %29, align 1, !dbg !601
  br label %if.end22, !dbg !602

if.end22:                                         ; preds = %if.then20, %if.end
  %30 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !603
  %n_bits23 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %30, i32 0, i32 0, !dbg !604
  %31 = load i32, i32* %n_bits23, align 8, !dbg !604
  %32 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !605
  %offset24 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %32, i32 0, i32 13, !dbg !606
  %33 = load i32, i32* %offset24, align 8, !dbg !607
  %add = add nsw i32 %33, %31, !dbg !607
  store i32 %add, i32* %offset24, align 8, !dbg !607
  %34 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !608
  %offset25 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %34, i32 0, i32 13, !dbg !610
  %35 = load i32, i32* %offset25, align 8, !dbg !610
  %36 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !611
  %n_bits26 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %36, i32 0, i32 0, !dbg !612
  %37 = load i32, i32* %n_bits26, align 8, !dbg !612
  %shl27 = shl i32 %37, 3, !dbg !613
  %cmp28 = icmp eq i32 %35, %shl27, !dbg !614
  br i1 %cmp28, label %if.then30, label %if.end41, !dbg !615

if.then30:                                        ; preds = %if.end22
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @buf, i32 0, i32 0), i8** %bp, align 8, !dbg !616
  %38 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !618
  %n_bits31 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %38, i32 0, i32 0, !dbg !619
  %39 = load i32, i32* %n_bits31, align 8, !dbg !619
  store i32 %39, i32* %bits, align 4, !dbg !620
  %40 = load i32, i32* %bits, align 4, !dbg !621
  %conv32 = sext i32 %40 to i64, !dbg !621
  %41 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !622
  %bytes_out = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %41, i32 0, i32 15, !dbg !623
  %42 = load i64, i64* %bytes_out, align 8, !dbg !624
  %add33 = add nsw i64 %42, %conv32, !dbg !624
  store i64 %add33, i64* %bytes_out, align 8, !dbg !624
  br label %do.body, !dbg !625

do.body:                                          ; preds = %do.cond, %if.then30
  %43 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !626
  %output_stream = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %43, i32 0, i32 23, !dbg !629
  %44 = load i32 (i8*, i8*, i32)*, i32 (i8*, i8*, i32)** %output_stream, align 8, !dbg !629
  %45 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !630
  %46 = bitcast %struct.cmcompress_stream* %45 to i8*, !dbg !630
  %47 = load i8*, i8** %bp, align 8, !dbg !631
  %call = call i32 %44(i8* %46, i8* %47, i32 1), !dbg !626
  %cmp34 = icmp ne i32 %call, 1, !dbg !632
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !633

if.then36:                                        ; preds = %do.body
  store i32 0, i32* %retval, align 4, !dbg !634
  br label %return, !dbg !634

if.end37:                                         ; preds = %do.body
  %48 = load i8*, i8** %bp, align 8, !dbg !636
  %incdec.ptr38 = getelementptr inbounds i8, i8* %48, i32 1, !dbg !636
  store i8* %incdec.ptr38, i8** %bp, align 8, !dbg !636
  br label %do.cond, !dbg !637

do.cond:                                          ; preds = %if.end37
  %49 = load i32, i32* %bits, align 4, !dbg !638
  %dec = add nsw i32 %49, -1, !dbg !638
  store i32 %dec, i32* %bits, align 4, !dbg !638
  %tobool39 = icmp ne i32 %dec, 0, !dbg !639
  br i1 %tobool39, label %do.body, label %do.end, !dbg !639

do.end:                                           ; preds = %do.cond
  %50 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !641
  %offset40 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %50, i32 0, i32 13, !dbg !642
  store i32 0, i32* %offset40, align 8, !dbg !643
  br label %if.end41, !dbg !644

if.end41:                                         ; preds = %do.end, %if.end22
  %51 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !645
  %free_ent = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %51, i32 0, i32 7, !dbg !647
  %52 = load i64, i64* %free_ent, align 8, !dbg !647
  %53 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !648
  %maxcode = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %53, i32 0, i32 2, !dbg !649
  %54 = load i64, i64* %maxcode, align 8, !dbg !649
  %cmp42 = icmp sgt i64 %52, %54, !dbg !650
  br i1 %cmp42, label %if.then46, label %lor.lhs.false, !dbg !651

lor.lhs.false:                                    ; preds = %if.end41
  %55 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !652
  %clear_flg = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %55, i32 0, i32 10, !dbg !654
  %56 = load i32, i32* %clear_flg, align 8, !dbg !654
  %cmp44 = icmp sgt i32 %56, 0, !dbg !655
  br i1 %cmp44, label %if.then46, label %if.end85, !dbg !656

if.then46:                                        ; preds = %lor.lhs.false, %if.end41
  %57 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !657
  %offset47 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %57, i32 0, i32 13, !dbg !660
  %58 = load i32, i32* %offset47, align 8, !dbg !660
  %cmp48 = icmp sgt i32 %58, 0, !dbg !661
  br i1 %cmp48, label %if.then50, label %if.end63, !dbg !662

if.then50:                                        ; preds = %if.then46
  %59 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !663
  %output_stream51 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %59, i32 0, i32 23, !dbg !666
  %60 = load i32 (i8*, i8*, i32)*, i32 (i8*, i8*, i32)** %output_stream51, align 8, !dbg !666
  %61 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !667
  %62 = bitcast %struct.cmcompress_stream* %61 to i8*, !dbg !667
  %63 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !668
  %n_bits52 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %63, i32 0, i32 0, !dbg !669
  %64 = load i32, i32* %n_bits52, align 8, !dbg !669
  %call53 = call i32 %60(i8* %62, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @buf, i32 0, i32 0), i32 %64), !dbg !663
  %65 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !670
  %n_bits54 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %65, i32 0, i32 0, !dbg !671
  %66 = load i32, i32* %n_bits54, align 8, !dbg !671
  %cmp55 = icmp ne i32 %call53, %66, !dbg !672
  br i1 %cmp55, label %if.then57, label %if.end58, !dbg !673

if.then57:                                        ; preds = %if.then50
  store i32 0, i32* %retval, align 4, !dbg !674
  br label %return, !dbg !674

if.end58:                                         ; preds = %if.then50
  %67 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !676
  %n_bits59 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %67, i32 0, i32 0, !dbg !677
  %68 = load i32, i32* %n_bits59, align 8, !dbg !677
  %conv60 = sext i32 %68 to i64, !dbg !676
  %69 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !678
  %bytes_out61 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %69, i32 0, i32 15, !dbg !679
  %70 = load i64, i64* %bytes_out61, align 8, !dbg !680
  %add62 = add nsw i64 %70, %conv60, !dbg !680
  store i64 %add62, i64* %bytes_out61, align 8, !dbg !680
  br label %if.end63, !dbg !681

if.end63:                                         ; preds = %if.end58, %if.then46
  %71 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !682
  %offset64 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %71, i32 0, i32 13, !dbg !683
  store i32 0, i32* %offset64, align 8, !dbg !684
  %72 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !685
  %clear_flg65 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %72, i32 0, i32 10, !dbg !687
  %73 = load i32, i32* %clear_flg65, align 8, !dbg !687
  %tobool66 = icmp ne i32 %73, 0, !dbg !685
  br i1 %tobool66, label %if.then67, label %if.else, !dbg !688

if.then67:                                        ; preds = %if.end63
  %74 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !689
  %n_bits68 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %74, i32 0, i32 0, !dbg !689
  store i32 9, i32* %n_bits68, align 8, !dbg !689
  %75 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !691
  %maxcode69 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %75, i32 0, i32 2, !dbg !692
  store i64 511, i64* %maxcode69, align 8, !dbg !693
  %76 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !694
  %clear_flg70 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %76, i32 0, i32 10, !dbg !695
  store i32 0, i32* %clear_flg70, align 8, !dbg !696
  br label %if.end84, !dbg !697

if.else:                                          ; preds = %if.end63
  %77 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !698
  %n_bits71 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %77, i32 0, i32 0, !dbg !700
  %78 = load i32, i32* %n_bits71, align 8, !dbg !701
  %inc = add nsw i32 %78, 1, !dbg !701
  store i32 %inc, i32* %n_bits71, align 8, !dbg !701
  %79 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !702
  %n_bits72 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %79, i32 0, i32 0, !dbg !704
  %80 = load i32, i32* %n_bits72, align 8, !dbg !704
  %81 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !705
  %maxbits = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %81, i32 0, i32 1, !dbg !706
  %82 = load i32, i32* %maxbits, align 4, !dbg !706
  %cmp73 = icmp eq i32 %80, %82, !dbg !707
  br i1 %cmp73, label %if.then75, label %if.else77, !dbg !708

if.then75:                                        ; preds = %if.else
  %83 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !709
  %maxmaxcode = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %83, i32 0, i32 3, !dbg !711
  %84 = load i64, i64* %maxmaxcode, align 8, !dbg !711
  %85 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !712
  %maxcode76 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %85, i32 0, i32 2, !dbg !713
  store i64 %84, i64* %maxcode76, align 8, !dbg !714
  br label %if.end83, !dbg !715

if.else77:                                        ; preds = %if.else
  %86 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !716
  %n_bits78 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %86, i32 0, i32 0, !dbg !716
  %87 = load i32, i32* %n_bits78, align 8, !dbg !716
  %shl79 = shl i32 1, %87, !dbg !716
  %sub80 = sub nsw i32 %shl79, 1, !dbg !716
  %conv81 = sext i32 %sub80 to i64, !dbg !716
  %88 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !718
  %maxcode82 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %88, i32 0, i32 2, !dbg !719
  store i64 %conv81, i64* %maxcode82, align 8, !dbg !720
  br label %if.end83

if.end83:                                         ; preds = %if.else77, %if.then75
  br label %if.end84

if.end84:                                         ; preds = %if.end83, %if.then67
  br label %if.end85, !dbg !721

if.end85:                                         ; preds = %if.end84, %lor.lhs.false
  br label %if.end113, !dbg !722

if.else86:                                        ; preds = %entry
  %89 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !723
  %offset87 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %89, i32 0, i32 13, !dbg !726
  %90 = load i32, i32* %offset87, align 8, !dbg !726
  %cmp88 = icmp sgt i32 %90, 0, !dbg !727
  br i1 %cmp88, label %if.then90, label %if.end106, !dbg !728

if.then90:                                        ; preds = %if.else86
  %91 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !729
  %offset91 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %91, i32 0, i32 13, !dbg !731
  %92 = load i32, i32* %offset91, align 8, !dbg !731
  %add92 = add nsw i32 %92, 7, !dbg !732
  %div = sdiv i32 %add92, 8, !dbg !733
  %93 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !734
  %offset93 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %93, i32 0, i32 13, !dbg !735
  store i32 %div, i32* %offset93, align 8, !dbg !736
  %94 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !737
  %output_stream94 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %94, i32 0, i32 23, !dbg !739
  %95 = load i32 (i8*, i8*, i32)*, i32 (i8*, i8*, i32)** %output_stream94, align 8, !dbg !739
  %96 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !740
  %97 = bitcast %struct.cmcompress_stream* %96 to i8*, !dbg !740
  %98 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !741
  %offset95 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %98, i32 0, i32 13, !dbg !742
  %99 = load i32, i32* %offset95, align 8, !dbg !742
  %call96 = call i32 %95(i8* %97, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @buf, i32 0, i32 0), i32 %99), !dbg !737
  %100 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !743
  %offset97 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %100, i32 0, i32 13, !dbg !744
  %101 = load i32, i32* %offset97, align 8, !dbg !744
  %cmp98 = icmp ne i32 %call96, %101, !dbg !745
  br i1 %cmp98, label %if.then100, label %if.end101, !dbg !746

if.then100:                                       ; preds = %if.then90
  store i32 0, i32* %retval, align 4, !dbg !747
  br label %return, !dbg !747

if.end101:                                        ; preds = %if.then90
  %102 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !749
  %offset102 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %102, i32 0, i32 13, !dbg !750
  %103 = load i32, i32* %offset102, align 8, !dbg !750
  %conv103 = sext i32 %103 to i64, !dbg !749
  %104 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !751
  %bytes_out104 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %104, i32 0, i32 15, !dbg !752
  %105 = load i64, i64* %bytes_out104, align 8, !dbg !753
  %add105 = add nsw i64 %105, %conv103, !dbg !753
  store i64 %add105, i64* %bytes_out104, align 8, !dbg !753
  br label %if.end106, !dbg !754

if.end106:                                        ; preds = %if.end101, %if.else86
  %106 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !755
  %offset107 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %106, i32 0, i32 13, !dbg !756
  store i32 0, i32* %offset107, align 8, !dbg !757
  %107 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !758
  %call108 = call i32 @fflush(%struct._IO_FILE* %107), !dbg !759
  %108 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !760
  %call109 = call i32 @ferror(%struct._IO_FILE* %108) #4, !dbg !762
  %tobool110 = icmp ne i32 %call109, 0, !dbg !762
  br i1 %tobool110, label %if.then111, label %if.end112, !dbg !763

if.then111:                                       ; preds = %if.end106
  store i32 0, i32* %retval, align 4, !dbg !764
  br label %return, !dbg !764

if.end112:                                        ; preds = %if.end106
  br label %if.end113

if.end113:                                        ; preds = %if.end112, %if.end85
  store i32 1, i32* %retval, align 4, !dbg !766
  br label %return, !dbg !766

return:                                           ; preds = %if.end113, %if.then111, %if.then100, %if.then57, %if.then36
  %109 = load i32, i32* %retval, align 4, !dbg !767
  ret i32 %109, !dbg !767
}

; Function Attrs: nounwind uwtable
define internal i32 @cl_block(%struct.cmcompress_stream* %cdata) #0 !dbg !72 {
entry:
  %retval = alloca i32, align 4
  %cdata.addr = alloca %struct.cmcompress_stream*, align 8
  %rat = alloca i64, align 8
  store %struct.cmcompress_stream* %cdata, %struct.cmcompress_stream** %cdata.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cmcompress_stream** %cdata.addr, metadata !768, metadata !93), !dbg !769
  call void @llvm.dbg.declare(metadata i64* %rat, metadata !770, metadata !93), !dbg !771
  %0 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !772
  %in_count = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %0, i32 0, i32 14, !dbg !773
  %1 = load i64, i64* %in_count, align 8, !dbg !773
  %add = add nsw i64 %1, 10000, !dbg !774
  %2 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !775
  %checkpoint = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %2, i32 0, i32 12, !dbg !776
  store i64 %add, i64* %checkpoint, align 8, !dbg !777
  %3 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !778
  %in_count1 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %3, i32 0, i32 14, !dbg !780
  %4 = load i64, i64* %in_count1, align 8, !dbg !780
  %cmp = icmp sgt i64 %4, 8388607, !dbg !781
  br i1 %cmp, label %if.then, label %if.else5, !dbg !782

if.then:                                          ; preds = %entry
  %5 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !783
  %bytes_out = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %5, i32 0, i32 15, !dbg !785
  %6 = load i64, i64* %bytes_out, align 8, !dbg !785
  %shr = ashr i64 %6, 8, !dbg !786
  store i64 %shr, i64* %rat, align 8, !dbg !787
  %7 = load i64, i64* %rat, align 8, !dbg !788
  %cmp2 = icmp eq i64 %7, 0, !dbg !790
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !791

if.then3:                                         ; preds = %if.then
  store i64 2147483647, i64* %rat, align 8, !dbg !792
  br label %if.end, !dbg !794

if.else:                                          ; preds = %if.then
  %8 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !795
  %in_count4 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %8, i32 0, i32 14, !dbg !797
  %9 = load i64, i64* %in_count4, align 8, !dbg !797
  %10 = load i64, i64* %rat, align 8, !dbg !798
  %div = sdiv i64 %9, %10, !dbg !799
  store i64 %div, i64* %rat, align 8, !dbg !800
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then3
  br label %if.end9, !dbg !801

if.else5:                                         ; preds = %entry
  %11 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !802
  %in_count6 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %11, i32 0, i32 14, !dbg !804
  %12 = load i64, i64* %in_count6, align 8, !dbg !804
  %shl = shl i64 %12, 8, !dbg !805
  %13 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !806
  %bytes_out7 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %13, i32 0, i32 15, !dbg !807
  %14 = load i64, i64* %bytes_out7, align 8, !dbg !807
  %div8 = sdiv i64 %shl, %14, !dbg !808
  store i64 %div8, i64* %rat, align 8, !dbg !809
  br label %if.end9

if.end9:                                          ; preds = %if.else5, %if.end
  %15 = load i64, i64* %rat, align 8, !dbg !810
  %16 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !812
  %ratio = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %16, i32 0, i32 11, !dbg !813
  %17 = load i64, i64* %ratio, align 8, !dbg !813
  %cmp10 = icmp sgt i64 %15, %17, !dbg !814
  br i1 %cmp10, label %if.then11, label %if.else13, !dbg !815

if.then11:                                        ; preds = %if.end9
  %18 = load i64, i64* %rat, align 8, !dbg !816
  %19 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !818
  %ratio12 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %19, i32 0, i32 11, !dbg !819
  store i64 %18, i64* %ratio12, align 8, !dbg !820
  br label %if.end17, !dbg !821

if.else13:                                        ; preds = %if.end9
  %20 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !822
  %ratio14 = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %20, i32 0, i32 11, !dbg !824
  store i64 0, i64* %ratio14, align 8, !dbg !825
  %21 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !826
  %22 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !827
  %hsize = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %22, i32 0, i32 6, !dbg !828
  %23 = load i64, i64* %hsize, align 8, !dbg !828
  call void @cl_hash(%struct.cmcompress_stream* %21, i64 %23), !dbg !829
  %24 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !830
  %free_ent = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %24, i32 0, i32 7, !dbg !831
  store i64 257, i64* %free_ent, align 8, !dbg !832
  %25 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !833
  %clear_flg = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %25, i32 0, i32 10, !dbg !834
  store i32 1, i32* %clear_flg, align 8, !dbg !835
  %26 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !836
  %call = call i32 @output(%struct.cmcompress_stream* %26, i64 256), !dbg !838
  %tobool = icmp ne i32 %call, 0, !dbg !838
  br i1 %tobool, label %if.end16, label %if.then15, !dbg !839

if.then15:                                        ; preds = %if.else13
  store i32 0, i32* %retval, align 4, !dbg !840
  br label %return, !dbg !840

if.end16:                                         ; preds = %if.else13
  br label %if.end17

if.end17:                                         ; preds = %if.end16, %if.then11
  store i32 1, i32* %retval, align 4, !dbg !842
  br label %return, !dbg !842

return:                                           ; preds = %if.end17, %if.then15
  %27 = load i32, i32* %retval, align 4, !dbg !843
  ret i32 %27, !dbg !843
}

; Function Attrs: nounwind uwtable
define i32 @cmcompress_compress_finalize(%struct.cmcompress_stream* %cdata) #0 !dbg !65 {
entry:
  %retval = alloca i32, align 4
  %cdata.addr = alloca %struct.cmcompress_stream*, align 8
  store %struct.cmcompress_stream* %cdata, %struct.cmcompress_stream** %cdata.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cmcompress_stream** %cdata.addr, metadata !844, metadata !93), !dbg !845
  %0 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !846
  %1 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !848
  %ent = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %1, i32 0, i32 17, !dbg !849
  %2 = load i64, i64* %ent, align 8, !dbg !849
  %call = call i32 @output(%struct.cmcompress_stream* %0, i64 %2), !dbg !850
  %tobool = icmp ne i32 %call, 0, !dbg !850
  br i1 %tobool, label %if.end, label %if.then, !dbg !851

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !852
  br label %return, !dbg !852

if.end:                                           ; preds = %entry
  %3 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !854
  %out_count = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %3, i32 0, i32 16, !dbg !855
  %4 = load i64, i64* %out_count, align 8, !dbg !856
  %inc = add nsw i64 %4, 1, !dbg !856
  store i64 %inc, i64* %out_count, align 8, !dbg !856
  %5 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !857
  %call1 = call i32 @output(%struct.cmcompress_stream* %5, i64 -1), !dbg !859
  %tobool2 = icmp ne i32 %call1, 0, !dbg !859
  br i1 %tobool2, label %if.end4, label %if.then3, !dbg !860

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !861
  br label %return, !dbg !861

if.end4:                                          ; preds = %if.end
  %6 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !863
  %bytes_out = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %6, i32 0, i32 15, !dbg !865
  %7 = load i64, i64* %bytes_out, align 8, !dbg !865
  %8 = load %struct.cmcompress_stream*, %struct.cmcompress_stream** %cdata.addr, align 8, !dbg !866
  %in_count = getelementptr inbounds %struct.cmcompress_stream, %struct.cmcompress_stream* %8, i32 0, i32 14, !dbg !867
  %9 = load i64, i64* %in_count, align 8, !dbg !867
  %cmp = icmp sgt i64 %7, %9, !dbg !868
  br i1 %cmp, label %if.then5, label %if.end6, !dbg !869

if.then5:                                         ; preds = %if.end4
  store i32 0, i32* %retval, align 4, !dbg !870
  br label %return, !dbg !870

if.end6:                                          ; preds = %if.end4
  store i32 1, i32* %retval, align 4, !dbg !872
  br label %return, !dbg !872

return:                                           ; preds = %if.end6, %if.then5, %if.then3, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !873
  ret i32 %10, !dbg !873
}

declare i32 @fflush(%struct._IO_FILE*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!89, !90}
!llvm.ident = !{!91}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !15, globals: !73)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcompress/cmcompress.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcompress")
!2 = !{}
!3 = !{!4, !5, !7, !8, !10, !12, !13, !14}
!4 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!7 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "count_int", file: !9, line: 126, baseType: !7)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcompress/cmcompress.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcompress")
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!12 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "code_int", file: !9, line: 117, baseType: !7)
!14 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!15 = !{!16, !58, !59, !65, !66, !69, !72}
!16 = distinct !DISubprogram(name: "cmcompress_compress_initialize", scope: !1, file: !1, line: 74, type: !17, isLocal: false, isDefinition: true, scopeLine: 75, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{!12, !19}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!20 = !DICompositeType(tag: DW_TAG_structure_type, name: "cmcompress_stream", file: !9, line: 137, size: 5521472, align: 64, elements: !21)
!21 = !{!22, !23, !24, !25, !26, !30, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !53, !57}
!22 = !DIDerivedType(tag: DW_TAG_member, name: "n_bits", scope: !20, file: !9, line: 139, baseType: !12, size: 32, align: 32)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "maxbits", scope: !20, file: !9, line: 140, baseType: !12, size: 32, align: 32, offset: 32)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "maxcode", scope: !20, file: !9, line: 141, baseType: !13, size: 64, align: 64, offset: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "maxmaxcode", scope: !20, file: !9, line: 142, baseType: !13, size: 64, align: 64, offset: 128)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "htab", scope: !20, file: !9, line: 144, baseType: !27, size: 4416064, align: 64, offset: 192)
!27 = !DICompositeType(tag: DW_TAG_array_type, baseType: !8, size: 4416064, align: 64, elements: !28)
!28 = !{!29}
!29 = !DISubrange(count: 69001)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "codetab", scope: !20, file: !9, line: 145, baseType: !31, size: 1104016, align: 16, offset: 4416256)
!31 = !DICompositeType(tag: DW_TAG_array_type, baseType: !14, size: 1104016, align: 16, elements: !28)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "hsize", scope: !20, file: !9, line: 147, baseType: !13, size: 64, align: 64, offset: 5520320)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "free_ent", scope: !20, file: !9, line: 148, baseType: !13, size: 64, align: 64, offset: 5520384)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "nomagic", scope: !20, file: !9, line: 149, baseType: !12, size: 32, align: 32, offset: 5520448)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "block_compress", scope: !20, file: !9, line: 155, baseType: !12, size: 32, align: 32, offset: 5520480)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "clear_flg", scope: !20, file: !9, line: 156, baseType: !12, size: 32, align: 32, offset: 5520512)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "ratio", scope: !20, file: !9, line: 157, baseType: !7, size: 64, align: 64, offset: 5520576)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "checkpoint", scope: !20, file: !9, line: 158, baseType: !8, size: 64, align: 64, offset: 5520640)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !20, file: !9, line: 166, baseType: !12, size: 32, align: 32, offset: 5520704)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "in_count", scope: !20, file: !9, line: 167, baseType: !7, size: 64, align: 64, offset: 5520768)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_out", scope: !20, file: !9, line: 168, baseType: !7, size: 64, align: 64, offset: 5520832)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "out_count", scope: !20, file: !9, line: 169, baseType: !7, size: 64, align: 64, offset: 5520896)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "ent", scope: !20, file: !9, line: 172, baseType: !13, size: 64, align: 64, offset: 5520960)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "hsize_reg", scope: !20, file: !9, line: 173, baseType: !13, size: 64, align: 64, offset: 5521024)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "hshift", scope: !20, file: !9, line: 174, baseType: !12, size: 32, align: 32, offset: 5521088)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "fcode", scope: !20, file: !9, line: 176, baseType: !7, size: 64, align: 64, offset: 5521152)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "first_pass", scope: !20, file: !9, line: 177, baseType: !12, size: 32, align: 32, offset: 5521216)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "input_stream", scope: !20, file: !9, line: 180, baseType: !49, size: 64, align: 64, offset: 5521280)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!12, !52}
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "output_stream", scope: !20, file: !9, line: 181, baseType: !54, size: 64, align: 64, offset: 5521344)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DISubroutineType(types: !56)
!56 = !{!12, !52, !5, !12}
!57 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !20, file: !9, line: 182, baseType: !52, size: 64, align: 64, offset: 5521408)
!58 = distinct !DISubprogram(name: "cmcompress_compress_start", scope: !1, file: !1, line: 320, type: !17, isLocal: false, isDefinition: true, scopeLine: 321, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!59 = distinct !DISubprogram(name: "cmcompress_compress", scope: !1, file: !1, line: 421, type: !60, isLocal: false, isDefinition: true, scopeLine: 422, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!60 = !DISubroutineType(types: !61)
!61 = !{!12, !19, !52, !62}
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !63, line: 62, baseType: !64)
!63 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcompress")
!64 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!65 = distinct !DISubprogram(name: "cmcompress_compress_finalize", scope: !1, file: !1, line: 507, type: !17, isLocal: false, isDefinition: true, scopeLine: 508, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!66 = distinct !DISubprogram(name: "cl_hash", scope: !1, file: !1, line: 92, type: !67, isLocal: true, isDefinition: true, scopeLine: 93, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!67 = !DISubroutineType(types: !68)
!68 = !{null, !19, !8}
!69 = distinct !DISubprogram(name: "output", scope: !1, file: !1, line: 148, type: !70, isLocal: true, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!70 = !DISubroutineType(types: !71)
!71 = !{!12, !19, !13}
!72 = distinct !DISubprogram(name: "cl_block", scope: !1, file: !1, line: 360, type: !17, isLocal: true, isDefinition: true, scopeLine: 361, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!73 = !{!74, !79, !80, !85}
!74 = !DIGlobalVariable(name: "lmask", scope: !0, file: !1, line: 144, type: !75, isLocal: false, isDefinition: true, variable: [9 x i8]* @lmask)
!75 = !DICompositeType(tag: DW_TAG_array_type, baseType: !76, size: 72, align: 8, elements: !77)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "char_type", file: !9, line: 132, baseType: !11)
!77 = !{!78}
!78 = !DISubrange(count: 9)
!79 = !DIGlobalVariable(name: "rmask", scope: !0, file: !1, line: 145, type: !75, isLocal: false, isDefinition: true, variable: [9 x i8]* @rmask)
!80 = !DIGlobalVariable(name: "magic_header", scope: !0, file: !1, line: 43, type: !81, isLocal: true, isDefinition: true, variable: [3 x i8]* @magic_header)
!81 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 24, align: 8, elements: !83)
!82 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !76)
!83 = !{!84}
!84 = !DISubrange(count: 3)
!85 = !DIGlobalVariable(name: "buf", scope: !0, file: !1, line: 141, type: !86, isLocal: true, isDefinition: true, variable: [16 x i8]* @buf)
!86 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 128, align: 8, elements: !87)
!87 = !{!88}
!88 = !DISubrange(count: 16)
!89 = !{i32 2, !"Dwarf Version", i32 4}
!90 = !{i32 2, !"Debug Info Version", i32 3}
!91 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!92 = !DILocalVariable(name: "cdata", arg: 1, scope: !16, file: !1, line: 74, type: !19)
!93 = !DIExpression()
!94 = !DILocation(line: 74, column: 62, scope: !16)
!95 = !DILocation(line: 76, column: 3, scope: !16)
!96 = !DILocation(line: 76, column: 10, scope: !16)
!97 = !DILocation(line: 76, column: 18, scope: !16)
!98 = !DILocation(line: 77, column: 3, scope: !16)
!99 = !DILocation(line: 77, column: 10, scope: !16)
!100 = !DILocation(line: 77, column: 21, scope: !16)
!101 = !DILocation(line: 78, column: 3, scope: !16)
!102 = !DILocation(line: 78, column: 10, scope: !16)
!103 = !DILocation(line: 78, column: 16, scope: !16)
!104 = !DILocation(line: 79, column: 3, scope: !16)
!105 = !DILocation(line: 79, column: 10, scope: !16)
!106 = !DILocation(line: 79, column: 19, scope: !16)
!107 = !DILocation(line: 80, column: 3, scope: !16)
!108 = !DILocation(line: 80, column: 10, scope: !16)
!109 = !DILocation(line: 80, column: 18, scope: !16)
!110 = !DILocation(line: 81, column: 3, scope: !16)
!111 = !DILocation(line: 81, column: 10, scope: !16)
!112 = !DILocation(line: 81, column: 25, scope: !16)
!113 = !DILocation(line: 82, column: 3, scope: !16)
!114 = !DILocation(line: 82, column: 10, scope: !16)
!115 = !DILocation(line: 82, column: 20, scope: !16)
!116 = !DILocation(line: 83, column: 3, scope: !16)
!117 = !DILocation(line: 83, column: 10, scope: !16)
!118 = !DILocation(line: 83, column: 16, scope: !16)
!119 = !DILocation(line: 84, column: 3, scope: !16)
!120 = !DILocation(line: 84, column: 10, scope: !16)
!121 = !DILocation(line: 84, column: 21, scope: !16)
!122 = !DILocation(line: 86, column: 3, scope: !16)
!123 = !DILocation(line: 86, column: 10, scope: !16)
!124 = !DILocation(line: 86, column: 23, scope: !16)
!125 = !DILocation(line: 87, column: 3, scope: !16)
!126 = !DILocation(line: 87, column: 10, scope: !16)
!127 = !DILocation(line: 87, column: 24, scope: !16)
!128 = !DILocation(line: 88, column: 3, scope: !16)
!129 = !DILocation(line: 88, column: 10, scope: !16)
!130 = !DILocation(line: 88, column: 22, scope: !16)
!131 = !DILocation(line: 89, column: 3, scope: !16)
!132 = !DILocalVariable(name: "cdata", arg: 1, scope: !58, file: !1, line: 320, type: !19)
!133 = !DILocation(line: 320, column: 57, scope: !58)
!134 = !DILocation(line: 323, column: 7, scope: !135)
!135 = distinct !DILexicalBlock(scope: !58, file: !1, line: 323, column: 7)
!136 = !DILocation(line: 323, column: 14, scope: !135)
!137 = !DILocation(line: 323, column: 22, scope: !135)
!138 = !DILocation(line: 323, column: 7, scope: !58)
!139 = !DILocalVariable(name: "headLast", scope: !140, file: !1, line: 325, type: !4)
!140 = distinct !DILexicalBlock(scope: !135, file: !1, line: 324, column: 5)
!141 = !DILocation(line: 325, column: 10, scope: !140)
!142 = !DILocation(line: 325, column: 28, scope: !140)
!143 = !DILocation(line: 325, column: 35, scope: !140)
!144 = !DILocation(line: 325, column: 45, scope: !140)
!145 = !DILocation(line: 325, column: 52, scope: !140)
!146 = !DILocation(line: 325, column: 43, scope: !140)
!147 = !DILocation(line: 325, column: 21, scope: !140)
!148 = !DILocation(line: 326, column: 5, scope: !140)
!149 = !DILocation(line: 326, column: 12, scope: !140)
!150 = !DILocation(line: 326, column: 26, scope: !140)
!151 = !DILocation(line: 327, column: 5, scope: !140)
!152 = !DILocation(line: 327, column: 12, scope: !140)
!153 = !DILocation(line: 327, column: 26, scope: !140)
!154 = !DILocation(line: 328, column: 15, scope: !155)
!155 = distinct !DILexicalBlock(scope: !140, file: !1, line: 328, column: 8)
!156 = !DILocation(line: 328, column: 8, scope: !155)
!157 = !DILocation(line: 328, column: 8, scope: !140)
!158 = !DILocation(line: 330, column: 7, scope: !159)
!159 = distinct !DILexicalBlock(scope: !155, file: !1, line: 329, column: 7)
!160 = !DILocation(line: 331, column: 7, scope: !159)
!161 = !DILocation(line: 332, column: 5, scope: !140)
!162 = !DILocation(line: 335, column: 3, scope: !58)
!163 = !DILocation(line: 335, column: 10, scope: !58)
!164 = !DILocation(line: 335, column: 17, scope: !58)
!165 = !DILocation(line: 336, column: 3, scope: !58)
!166 = !DILocation(line: 336, column: 10, scope: !58)
!167 = !DILocation(line: 336, column: 20, scope: !58)
!168 = !DILocation(line: 337, column: 3, scope: !58)
!169 = !DILocation(line: 337, column: 10, scope: !58)
!170 = !DILocation(line: 337, column: 20, scope: !58)
!171 = !DILocation(line: 338, column: 3, scope: !58)
!172 = !DILocation(line: 338, column: 10, scope: !58)
!173 = !DILocation(line: 338, column: 20, scope: !58)
!174 = !DILocation(line: 339, column: 3, scope: !58)
!175 = !DILocation(line: 339, column: 10, scope: !58)
!176 = !DILocation(line: 339, column: 16, scope: !58)
!177 = !DILocation(line: 340, column: 3, scope: !58)
!178 = !DILocation(line: 340, column: 10, scope: !58)
!179 = !DILocation(line: 340, column: 19, scope: !58)
!180 = !DILocation(line: 341, column: 3, scope: !58)
!181 = !DILocation(line: 341, column: 10, scope: !58)
!182 = !DILocation(line: 341, column: 21, scope: !58)
!183 = !DILocation(line: 342, column: 20, scope: !58)
!184 = !DILocation(line: 342, column: 3, scope: !58)
!185 = !DILocation(line: 342, column: 10, scope: !58)
!186 = !DILocation(line: 342, column: 18, scope: !58)
!187 = !DILocation(line: 343, column: 23, scope: !58)
!188 = !DILocation(line: 343, column: 30, scope: !58)
!189 = !DILocation(line: 343, column: 22, scope: !58)
!190 = !DILocation(line: 343, column: 21, scope: !58)
!191 = !DILocation(line: 343, column: 3, scope: !58)
!192 = !DILocation(line: 343, column: 10, scope: !58)
!193 = !DILocation(line: 343, column: 19, scope: !58)
!194 = !DILocation(line: 345, column: 3, scope: !58)
!195 = !DILocation(line: 345, column: 10, scope: !58)
!196 = !DILocation(line: 345, column: 21, scope: !58)
!197 = !DILocation(line: 347, column: 3, scope: !58)
!198 = !DILocation(line: 347, column: 10, scope: !58)
!199 = !DILocation(line: 347, column: 17, scope: !58)
!200 = !DILocation(line: 348, column: 31, scope: !201)
!201 = distinct !DILexicalBlock(scope: !58, file: !1, line: 348, column: 3)
!202 = !DILocation(line: 348, column: 38, scope: !201)
!203 = !DILocation(line: 348, column: 9, scope: !201)
!204 = !DILocation(line: 348, column: 16, scope: !201)
!205 = !DILocation(line: 348, column: 22, scope: !201)
!206 = !DILocation(line: 348, column: 46, scope: !207)
!207 = !DILexicalBlockFile(scope: !208, file: !1, discriminator: 1)
!208 = distinct !DILexicalBlock(scope: !201, file: !1, line: 348, column: 3)
!209 = !DILocation(line: 348, column: 53, scope: !207)
!210 = !DILocation(line: 348, column: 59, scope: !207)
!211 = !DILocation(line: 348, column: 3, scope: !207)
!212 = !DILocation(line: 350, column: 5, scope: !213)
!213 = distinct !DILexicalBlock(scope: !208, file: !1, line: 349, column: 5)
!214 = !DILocation(line: 350, column: 12, scope: !213)
!215 = !DILocation(line: 350, column: 18, scope: !213)
!216 = !DILocation(line: 351, column: 5, scope: !213)
!217 = !DILocation(line: 348, column: 69, scope: !218)
!218 = !DILexicalBlockFile(scope: !208, file: !1, discriminator: 2)
!219 = !DILocation(line: 348, column: 76, scope: !218)
!220 = !DILocation(line: 348, column: 82, scope: !218)
!221 = !DILocation(line: 348, column: 3, scope: !218)
!222 = !DILocation(line: 352, column: 23, scope: !58)
!223 = !DILocation(line: 352, column: 30, scope: !58)
!224 = !DILocation(line: 352, column: 21, scope: !58)
!225 = !DILocation(line: 352, column: 3, scope: !58)
!226 = !DILocation(line: 352, column: 10, scope: !58)
!227 = !DILocation(line: 352, column: 17, scope: !58)
!228 = !DILocation(line: 354, column: 22, scope: !58)
!229 = !DILocation(line: 354, column: 29, scope: !58)
!230 = !DILocation(line: 354, column: 3, scope: !58)
!231 = !DILocation(line: 354, column: 10, scope: !58)
!232 = !DILocation(line: 354, column: 20, scope: !58)
!233 = !DILocation(line: 355, column: 11, scope: !58)
!234 = !DILocation(line: 355, column: 30, scope: !58)
!235 = !DILocation(line: 355, column: 37, scope: !58)
!236 = !DILocation(line: 355, column: 3, scope: !58)
!237 = !DILocation(line: 357, column: 3, scope: !58)
!238 = !DILocalVariable(name: "cdata", arg: 1, scope: !66, file: !1, line: 92, type: !19)
!239 = !DILocation(line: 92, column: 47, scope: !66)
!240 = !DILocalVariable(name: "hsize", arg: 2, scope: !66, file: !1, line: 92, type: !8)
!241 = !DILocation(line: 92, column: 64, scope: !66)
!242 = !DILocalVariable(name: "htab_p", scope: !66, file: !1, line: 94, type: !243)
!243 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!244 = !DILocation(line: 94, column: 23, scope: !66)
!245 = !DILocation(line: 94, column: 32, scope: !66)
!246 = !DILocation(line: 94, column: 39, scope: !66)
!247 = !DILocation(line: 94, column: 44, scope: !66)
!248 = !DILocation(line: 94, column: 43, scope: !66)
!249 = !DILocalVariable(name: "i", scope: !66, file: !1, line: 95, type: !7)
!250 = !DILocation(line: 95, column: 17, scope: !66)
!251 = !DILocalVariable(name: "m1", scope: !66, file: !1, line: 96, type: !7)
!252 = !DILocation(line: 96, column: 17, scope: !66)
!253 = !DILocation(line: 98, column: 7, scope: !66)
!254 = !DILocation(line: 98, column: 13, scope: !66)
!255 = !DILocation(line: 98, column: 5, scope: !66)
!256 = !DILocation(line: 99, column: 3, scope: !66)
!257 = !DILocation(line: 101, column: 20, scope: !258)
!258 = distinct !DILexicalBlock(scope: !66, file: !1, line: 100, column: 5)
!259 = !DILocation(line: 101, column: 7, scope: !258)
!260 = !DILocation(line: 101, column: 13, scope: !258)
!261 = !DILocation(line: 101, column: 18, scope: !258)
!262 = !DILocation(line: 102, column: 20, scope: !258)
!263 = !DILocation(line: 102, column: 7, scope: !258)
!264 = !DILocation(line: 102, column: 13, scope: !258)
!265 = !DILocation(line: 102, column: 18, scope: !258)
!266 = !DILocation(line: 103, column: 20, scope: !258)
!267 = !DILocation(line: 103, column: 7, scope: !258)
!268 = !DILocation(line: 103, column: 13, scope: !258)
!269 = !DILocation(line: 103, column: 18, scope: !258)
!270 = !DILocation(line: 104, column: 20, scope: !258)
!271 = !DILocation(line: 104, column: 7, scope: !258)
!272 = !DILocation(line: 104, column: 13, scope: !258)
!273 = !DILocation(line: 104, column: 18, scope: !258)
!274 = !DILocation(line: 105, column: 20, scope: !258)
!275 = !DILocation(line: 105, column: 7, scope: !258)
!276 = !DILocation(line: 105, column: 13, scope: !258)
!277 = !DILocation(line: 105, column: 18, scope: !258)
!278 = !DILocation(line: 106, column: 20, scope: !258)
!279 = !DILocation(line: 106, column: 7, scope: !258)
!280 = !DILocation(line: 106, column: 13, scope: !258)
!281 = !DILocation(line: 106, column: 18, scope: !258)
!282 = !DILocation(line: 107, column: 20, scope: !258)
!283 = !DILocation(line: 107, column: 7, scope: !258)
!284 = !DILocation(line: 107, column: 13, scope: !258)
!285 = !DILocation(line: 107, column: 18, scope: !258)
!286 = !DILocation(line: 108, column: 19, scope: !258)
!287 = !DILocation(line: 108, column: 7, scope: !258)
!288 = !DILocation(line: 108, column: 13, scope: !258)
!289 = !DILocation(line: 108, column: 17, scope: !258)
!290 = !DILocation(line: 109, column: 19, scope: !258)
!291 = !DILocation(line: 109, column: 7, scope: !258)
!292 = !DILocation(line: 109, column: 13, scope: !258)
!293 = !DILocation(line: 109, column: 17, scope: !258)
!294 = !DILocation(line: 110, column: 19, scope: !258)
!295 = !DILocation(line: 110, column: 7, scope: !258)
!296 = !DILocation(line: 110, column: 13, scope: !258)
!297 = !DILocation(line: 110, column: 17, scope: !258)
!298 = !DILocation(line: 111, column: 19, scope: !258)
!299 = !DILocation(line: 111, column: 7, scope: !258)
!300 = !DILocation(line: 111, column: 13, scope: !258)
!301 = !DILocation(line: 111, column: 17, scope: !258)
!302 = !DILocation(line: 112, column: 19, scope: !258)
!303 = !DILocation(line: 112, column: 7, scope: !258)
!304 = !DILocation(line: 112, column: 13, scope: !258)
!305 = !DILocation(line: 112, column: 17, scope: !258)
!306 = !DILocation(line: 113, column: 19, scope: !258)
!307 = !DILocation(line: 113, column: 7, scope: !258)
!308 = !DILocation(line: 113, column: 13, scope: !258)
!309 = !DILocation(line: 113, column: 17, scope: !258)
!310 = !DILocation(line: 114, column: 19, scope: !258)
!311 = !DILocation(line: 114, column: 7, scope: !258)
!312 = !DILocation(line: 114, column: 13, scope: !258)
!313 = !DILocation(line: 114, column: 17, scope: !258)
!314 = !DILocation(line: 115, column: 19, scope: !258)
!315 = !DILocation(line: 115, column: 7, scope: !258)
!316 = !DILocation(line: 115, column: 13, scope: !258)
!317 = !DILocation(line: 115, column: 17, scope: !258)
!318 = !DILocation(line: 116, column: 19, scope: !258)
!319 = !DILocation(line: 116, column: 7, scope: !258)
!320 = !DILocation(line: 116, column: 13, scope: !258)
!321 = !DILocation(line: 116, column: 17, scope: !258)
!322 = !DILocation(line: 117, column: 12, scope: !258)
!323 = !DILocation(line: 118, column: 5, scope: !258)
!324 = !DILocation(line: 119, column: 13, scope: !66)
!325 = !DILocation(line: 119, column: 20, scope: !66)
!326 = !DILocation(line: 118, column: 5, scope: !327)
!327 = !DILexicalBlockFile(scope: !258, file: !1, discriminator: 1)
!328 = !DILocation(line: 120, column: 11, scope: !329)
!329 = distinct !DILexicalBlock(scope: !66, file: !1, line: 120, column: 3)
!330 = !DILocation(line: 120, column: 9, scope: !329)
!331 = !DILocation(line: 120, column: 18, scope: !332)
!332 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 1)
!333 = distinct !DILexicalBlock(scope: !329, file: !1, line: 120, column: 3)
!334 = !DILocation(line: 120, column: 20, scope: !332)
!335 = !DILocation(line: 120, column: 3, scope: !332)
!336 = !DILocation(line: 122, column: 17, scope: !337)
!337 = distinct !DILexicalBlock(scope: !333, file: !1, line: 121, column: 5)
!338 = !DILocation(line: 122, column: 6, scope: !337)
!339 = !DILocation(line: 122, column: 15, scope: !337)
!340 = !DILocation(line: 123, column: 5, scope: !337)
!341 = !DILocation(line: 120, column: 26, scope: !342)
!342 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 2)
!343 = !DILocation(line: 120, column: 3, scope: !342)
!344 = !DILocation(line: 124, column: 1, scope: !66)
!345 = !DILocalVariable(name: "cdata", arg: 1, scope: !59, file: !1, line: 421, type: !19)
!346 = !DILocation(line: 421, column: 51, scope: !59)
!347 = !DILocalVariable(name: "buff", arg: 2, scope: !59, file: !1, line: 421, type: !52)
!348 = !DILocation(line: 421, column: 64, scope: !59)
!349 = !DILocalVariable(name: "n", arg: 3, scope: !59, file: !1, line: 421, type: !62)
!350 = !DILocation(line: 421, column: 77, scope: !59)
!351 = !DILocalVariable(name: "i", scope: !59, file: !1, line: 423, type: !13)
!352 = !DILocation(line: 423, column: 21, scope: !59)
!353 = !DILocalVariable(name: "c", scope: !59, file: !1, line: 424, type: !12)
!354 = !DILocation(line: 424, column: 16, scope: !59)
!355 = !DILocalVariable(name: "disp", scope: !59, file: !1, line: 425, type: !12)
!356 = !DILocation(line: 425, column: 16, scope: !59)
!357 = !DILocalVariable(name: "input_buffer", scope: !59, file: !1, line: 427, type: !10)
!358 = !DILocation(line: 427, column: 18, scope: !59)
!359 = !DILocation(line: 427, column: 49, scope: !59)
!360 = !DILocalVariable(name: "cc", scope: !59, file: !1, line: 429, type: !62)
!361 = !DILocation(line: 429, column: 10, scope: !59)
!362 = !DILocation(line: 433, column: 8, scope: !363)
!363 = distinct !DILexicalBlock(scope: !59, file: !1, line: 433, column: 8)
!364 = !DILocation(line: 433, column: 15, scope: !363)
!365 = !DILocation(line: 433, column: 8, scope: !59)
!366 = !DILocation(line: 435, column: 18, scope: !367)
!367 = distinct !DILexicalBlock(scope: !363, file: !1, line: 434, column: 5)
!368 = !DILocation(line: 435, column: 5, scope: !367)
!369 = !DILocation(line: 435, column: 12, scope: !367)
!370 = !DILocation(line: 435, column: 16, scope: !367)
!371 = !DILocation(line: 436, column: 5, scope: !367)
!372 = !DILocation(line: 437, column: 5, scope: !367)
!373 = !DILocation(line: 438, column: 5, scope: !367)
!374 = !DILocation(line: 438, column: 12, scope: !367)
!375 = !DILocation(line: 438, column: 23, scope: !367)
!376 = !DILocation(line: 439, column: 5, scope: !367)
!377 = !DILocation(line: 441, column: 12, scope: !378)
!378 = distinct !DILexicalBlock(scope: !59, file: !1, line: 441, column: 3)
!379 = !DILocation(line: 441, column: 9, scope: !378)
!380 = !DILocation(line: 441, column: 17, scope: !381)
!381 = !DILexicalBlockFile(scope: !382, file: !1, discriminator: 1)
!382 = distinct !DILexicalBlock(scope: !378, file: !1, line: 441, column: 3)
!383 = !DILocation(line: 441, column: 22, scope: !381)
!384 = !DILocation(line: 441, column: 20, scope: !381)
!385 = !DILocation(line: 441, column: 3, scope: !381)
!386 = !DILocation(line: 443, column: 22, scope: !387)
!387 = distinct !DILexicalBlock(scope: !382, file: !1, line: 442, column: 5)
!388 = !DILocation(line: 443, column: 9, scope: !387)
!389 = !DILocation(line: 443, column: 7, scope: !387)
!390 = !DILocation(line: 444, column: 5, scope: !387)
!391 = !DILocation(line: 444, column: 12, scope: !387)
!392 = !DILocation(line: 444, column: 20, scope: !387)
!393 = !DILocation(line: 445, column: 36, scope: !387)
!394 = !DILocation(line: 445, column: 29, scope: !387)
!395 = !DILocation(line: 445, column: 41, scope: !387)
!396 = !DILocation(line: 445, column: 48, scope: !387)
!397 = !DILocation(line: 445, column: 38, scope: !387)
!398 = !DILocation(line: 445, column: 59, scope: !387)
!399 = !DILocation(line: 445, column: 66, scope: !387)
!400 = !DILocation(line: 445, column: 57, scope: !387)
!401 = !DILocation(line: 445, column: 5, scope: !387)
!402 = !DILocation(line: 445, column: 12, scope: !387)
!403 = !DILocation(line: 445, column: 18, scope: !387)
!404 = !DILocation(line: 446, column: 11, scope: !387)
!405 = !DILocation(line: 446, column: 16, scope: !387)
!406 = !DILocation(line: 446, column: 23, scope: !387)
!407 = !DILocation(line: 446, column: 13, scope: !387)
!408 = !DILocation(line: 446, column: 10, scope: !387)
!409 = !DILocation(line: 446, column: 33, scope: !387)
!410 = !DILocation(line: 446, column: 40, scope: !387)
!411 = !DILocation(line: 446, column: 31, scope: !387)
!412 = !DILocation(line: 446, column: 7, scope: !387)
!413 = !DILocation(line: 448, column: 10, scope: !414)
!414 = distinct !DILexicalBlock(scope: !387, file: !1, line: 448, column: 10)
!415 = !DILocation(line: 448, column: 24, scope: !414)
!416 = !DILocation(line: 448, column: 31, scope: !414)
!417 = !DILocation(line: 448, column: 21, scope: !414)
!418 = !DILocation(line: 448, column: 10, scope: !387)
!419 = !DILocation(line: 450, column: 20, scope: !420)
!420 = distinct !DILexicalBlock(scope: !414, file: !1, line: 449, column: 7)
!421 = !DILocation(line: 450, column: 7, scope: !420)
!422 = !DILocation(line: 450, column: 14, scope: !420)
!423 = !DILocation(line: 450, column: 18, scope: !420)
!424 = !DILocation(line: 451, column: 7, scope: !420)
!425 = !DILocation(line: 453, column: 21, scope: !426)
!426 = distinct !DILexicalBlock(scope: !414, file: !1, line: 453, column: 15)
!427 = !DILocation(line: 453, column: 32, scope: !426)
!428 = !DILocation(line: 453, column: 15, scope: !414)
!429 = !DILocation(line: 455, column: 7, scope: !430)
!430 = distinct !DILexicalBlock(scope: !426, file: !1, line: 454, column: 7)
!431 = !DILocation(line: 457, column: 18, scope: !387)
!432 = !DILocation(line: 457, column: 25, scope: !387)
!433 = !DILocation(line: 457, column: 37, scope: !387)
!434 = !DILocation(line: 457, column: 35, scope: !387)
!435 = !DILocation(line: 457, column: 12, scope: !387)
!436 = !DILocation(line: 457, column: 10, scope: !387)
!437 = !DILocation(line: 458, column: 10, scope: !438)
!438 = distinct !DILexicalBlock(scope: !387, file: !1, line: 458, column: 10)
!439 = !DILocation(line: 458, column: 12, scope: !438)
!440 = !DILocation(line: 458, column: 10, scope: !387)
!441 = !DILocation(line: 460, column: 12, scope: !442)
!442 = distinct !DILexicalBlock(scope: !438, file: !1, line: 459, column: 7)
!443 = !DILocation(line: 461, column: 7, scope: !442)
!444 = !DILocation(line: 458, column: 15, scope: !445)
!445 = !DILexicalBlockFile(scope: !438, file: !1, discriminator: 1)
!446 = !DILocation(line: 463, column: 16, scope: !447)
!447 = distinct !DILexicalBlock(scope: !387, file: !1, line: 463, column: 10)
!448 = !DILocation(line: 463, column: 13, scope: !447)
!449 = !DILocation(line: 463, column: 22, scope: !447)
!450 = !DILocation(line: 463, column: 10, scope: !387)
!451 = !DILocation(line: 465, column: 12, scope: !452)
!452 = distinct !DILexicalBlock(scope: !447, file: !1, line: 464, column: 7)
!453 = !DILocation(line: 465, column: 19, scope: !452)
!454 = !DILocation(line: 465, column: 9, scope: !452)
!455 = !DILocation(line: 466, column: 7, scope: !452)
!456 = !DILocation(line: 468, column: 10, scope: !457)
!457 = distinct !DILexicalBlock(scope: !387, file: !1, line: 468, column: 10)
!458 = !DILocation(line: 468, column: 24, scope: !457)
!459 = !DILocation(line: 468, column: 31, scope: !457)
!460 = !DILocation(line: 468, column: 21, scope: !457)
!461 = !DILocation(line: 468, column: 10, scope: !387)
!462 = !DILocation(line: 470, column: 20, scope: !463)
!463 = distinct !DILexicalBlock(scope: !457, file: !1, line: 469, column: 7)
!464 = !DILocation(line: 470, column: 7, scope: !463)
!465 = !DILocation(line: 470, column: 14, scope: !463)
!466 = !DILocation(line: 470, column: 18, scope: !463)
!467 = !DILocation(line: 471, column: 7, scope: !463)
!468 = !DILocation(line: 473, column: 16, scope: !469)
!469 = distinct !DILexicalBlock(scope: !387, file: !1, line: 473, column: 10)
!470 = !DILocation(line: 473, column: 27, scope: !469)
!471 = !DILocation(line: 473, column: 10, scope: !387)
!472 = !DILocation(line: 475, column: 7, scope: !473)
!473 = distinct !DILexicalBlock(scope: !469, file: !1, line: 474, column: 7)
!474 = !DILocation(line: 473, column: 29, scope: !475)
!475 = !DILexicalBlockFile(scope: !469, file: !1, discriminator: 1)
!476 = !DILocation(line: 478, column: 18, scope: !477)
!477 = distinct !DILexicalBlock(scope: !387, file: !1, line: 478, column: 10)
!478 = !DILocation(line: 478, column: 36, scope: !477)
!479 = !DILocation(line: 478, column: 43, scope: !477)
!480 = !DILocation(line: 478, column: 11, scope: !477)
!481 = !DILocation(line: 478, column: 10, scope: !387)
!482 = !DILocation(line: 480, column: 7, scope: !483)
!483 = distinct !DILexicalBlock(scope: !477, file: !1, line: 479, column: 7)
!484 = !DILocation(line: 482, column: 5, scope: !387)
!485 = !DILocation(line: 482, column: 12, scope: !387)
!486 = !DILocation(line: 482, column: 21, scope: !387)
!487 = !DILocation(line: 483, column: 18, scope: !387)
!488 = !DILocation(line: 483, column: 5, scope: !387)
!489 = !DILocation(line: 483, column: 12, scope: !387)
!490 = !DILocation(line: 483, column: 16, scope: !387)
!491 = !DILocation(line: 488, column: 7, scope: !492)
!492 = distinct !DILexicalBlock(scope: !387, file: !1, line: 488, column: 7)
!493 = !DILocation(line: 488, column: 14, scope: !492)
!494 = !DILocation(line: 488, column: 25, scope: !492)
!495 = !DILocation(line: 488, column: 32, scope: !492)
!496 = !DILocation(line: 488, column: 23, scope: !492)
!497 = !DILocation(line: 488, column: 7, scope: !387)
!498 = !DILocation(line: 492, column: 40, scope: !499)
!499 = distinct !DILexicalBlock(scope: !492, file: !1, line: 491, column: 7)
!500 = !DILocation(line: 492, column: 47, scope: !499)
!501 = !DILocation(line: 492, column: 55, scope: !499)
!502 = !DILocation(line: 492, column: 23, scope: !499)
!503 = !DILocation(line: 492, column: 7, scope: !499)
!504 = !DILocation(line: 492, column: 21, scope: !499)
!505 = !DILocation(line: 493, column: 20, scope: !499)
!506 = !DILocation(line: 493, column: 27, scope: !499)
!507 = !DILocation(line: 493, column: 7, scope: !499)
!508 = !DILocation(line: 493, column: 18, scope: !499)
!509 = !DILocation(line: 494, column: 7, scope: !499)
!510 = !DILocation(line: 495, column: 26, scope: !511)
!511 = distinct !DILexicalBlock(scope: !492, file: !1, line: 495, column: 15)
!512 = !DILocation(line: 495, column: 33, scope: !511)
!513 = !DILocation(line: 495, column: 45, scope: !511)
!514 = !DILocation(line: 495, column: 52, scope: !511)
!515 = !DILocation(line: 495, column: 42, scope: !511)
!516 = !DILocation(line: 495, column: 63, scope: !511)
!517 = !DILocation(line: 495, column: 66, scope: !518)
!518 = !DILexicalBlockFile(scope: !511, file: !1, discriminator: 1)
!519 = !DILocation(line: 495, column: 73, scope: !518)
!520 = !DILocation(line: 495, column: 15, scope: !518)
!521 = !DILocation(line: 497, column: 23, scope: !522)
!522 = distinct !DILexicalBlock(scope: !523, file: !1, line: 497, column: 12)
!523 = distinct !DILexicalBlock(scope: !511, file: !1, line: 496, column: 7)
!524 = !DILocation(line: 497, column: 13, scope: !522)
!525 = !DILocation(line: 497, column: 12, scope: !523)
!526 = !DILocation(line: 499, column: 9, scope: !527)
!527 = distinct !DILexicalBlock(scope: !522, file: !1, line: 498, column: 9)
!528 = !DILocation(line: 501, column: 7, scope: !523)
!529 = !DILocation(line: 502, column: 5, scope: !387)
!530 = !DILocation(line: 441, column: 25, scope: !531)
!531 = !DILexicalBlockFile(scope: !382, file: !1, discriminator: 2)
!532 = !DILocation(line: 441, column: 3, scope: !531)
!533 = !DILocation(line: 504, column: 3, scope: !59)
!534 = !DILocation(line: 505, column: 1, scope: !59)
!535 = !DILocalVariable(name: "cdata", arg: 1, scope: !69, file: !1, line: 148, type: !19)
!536 = !DILocation(line: 148, column: 45, scope: !69)
!537 = !DILocalVariable(name: "code", arg: 2, scope: !69, file: !1, line: 148, type: !13)
!538 = !DILocation(line: 148, column: 62, scope: !69)
!539 = !DILocalVariable(name: "r_off", scope: !69, file: !1, line: 158, type: !12)
!540 = !DILocation(line: 158, column: 16, scope: !69)
!541 = !DILocation(line: 158, column: 24, scope: !69)
!542 = !DILocation(line: 158, column: 31, scope: !69)
!543 = !DILocalVariable(name: "bits", scope: !69, file: !1, line: 158, type: !12)
!544 = !DILocation(line: 158, column: 39, scope: !69)
!545 = !DILocation(line: 158, column: 45, scope: !69)
!546 = !DILocation(line: 158, column: 52, scope: !69)
!547 = !DILocalVariable(name: "bp", scope: !69, file: !1, line: 159, type: !548)
!548 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64, align: 64)
!549 = !DILocation(line: 159, column: 19, scope: !69)
!550 = !DILocation(line: 168, column: 8, scope: !551)
!551 = distinct !DILexicalBlock(scope: !69, file: !1, line: 168, column: 8)
!552 = !DILocation(line: 168, column: 13, scope: !551)
!553 = !DILocation(line: 168, column: 8, scope: !69)
!554 = !DILocation(line: 187, column: 12, scope: !555)
!555 = distinct !DILexicalBlock(scope: !551, file: !1, line: 169, column: 5)
!556 = !DILocation(line: 187, column: 18, scope: !555)
!557 = !DILocation(line: 187, column: 8, scope: !555)
!558 = !DILocation(line: 188, column: 11, scope: !555)
!559 = !DILocation(line: 193, column: 20, scope: !555)
!560 = !DILocation(line: 193, column: 19, scope: !555)
!561 = !DILocation(line: 193, column: 31, scope: !555)
!562 = !DILocation(line: 193, column: 25, scope: !555)
!563 = !DILocation(line: 193, column: 23, scope: !555)
!564 = !DILocation(line: 193, column: 18, scope: !555)
!565 = !DILocation(line: 193, column: 43, scope: !555)
!566 = !DILocation(line: 193, column: 51, scope: !555)
!567 = !DILocation(line: 193, column: 48, scope: !555)
!568 = !DILocation(line: 193, column: 66, scope: !555)
!569 = !DILocation(line: 193, column: 60, scope: !555)
!570 = !DILocation(line: 193, column: 58, scope: !555)
!571 = !DILocation(line: 193, column: 39, scope: !555)
!572 = !DILocation(line: 193, column: 11, scope: !555)
!573 = !DILocation(line: 193, column: 6, scope: !555)
!574 = !DILocation(line: 193, column: 9, scope: !555)
!575 = !DILocation(line: 194, column: 7, scope: !555)
!576 = !DILocation(line: 195, column: 18, scope: !555)
!577 = !DILocation(line: 195, column: 16, scope: !555)
!578 = !DILocation(line: 195, column: 10, scope: !555)
!579 = !DILocation(line: 196, column: 18, scope: !555)
!580 = !DILocation(line: 196, column: 16, scope: !555)
!581 = !DILocation(line: 196, column: 10, scope: !555)
!582 = !DILocation(line: 198, column: 10, scope: !583)
!583 = distinct !DILexicalBlock(scope: !555, file: !1, line: 198, column: 10)
!584 = !DILocation(line: 198, column: 15, scope: !583)
!585 = !DILocation(line: 198, column: 10, scope: !555)
!586 = !DILocation(line: 200, column: 22, scope: !587)
!587 = distinct !DILexicalBlock(scope: !583, file: !1, line: 199, column: 7)
!588 = !DILocation(line: 200, column: 15, scope: !587)
!589 = !DILocation(line: 200, column: 10, scope: !587)
!590 = !DILocation(line: 200, column: 13, scope: !587)
!591 = !DILocation(line: 201, column: 12, scope: !587)
!592 = !DILocation(line: 202, column: 12, scope: !587)
!593 = !DILocation(line: 203, column: 7, scope: !587)
!594 = !DILocation(line: 205, column: 8, scope: !595)
!595 = distinct !DILexicalBlock(scope: !555, file: !1, line: 205, column: 8)
!596 = !DILocation(line: 205, column: 8, scope: !555)
!597 = !DILocation(line: 207, column: 20, scope: !598)
!598 = distinct !DILexicalBlock(scope: !595, file: !1, line: 206, column: 7)
!599 = !DILocation(line: 207, column: 13, scope: !598)
!600 = !DILocation(line: 207, column: 8, scope: !598)
!601 = !DILocation(line: 207, column: 11, scope: !598)
!602 = !DILocation(line: 208, column: 7, scope: !598)
!603 = !DILocation(line: 210, column: 22, scope: !555)
!604 = !DILocation(line: 210, column: 29, scope: !555)
!605 = !DILocation(line: 210, column: 5, scope: !555)
!606 = !DILocation(line: 210, column: 12, scope: !555)
!607 = !DILocation(line: 210, column: 19, scope: !555)
!608 = !DILocation(line: 211, column: 10, scope: !609)
!609 = distinct !DILexicalBlock(scope: !555, file: !1, line: 211, column: 10)
!610 = !DILocation(line: 211, column: 17, scope: !609)
!611 = !DILocation(line: 211, column: 28, scope: !609)
!612 = !DILocation(line: 211, column: 35, scope: !609)
!613 = !DILocation(line: 211, column: 42, scope: !609)
!614 = !DILocation(line: 211, column: 24, scope: !609)
!615 = !DILocation(line: 211, column: 10, scope: !555)
!616 = !DILocation(line: 213, column: 10, scope: !617)
!617 = distinct !DILexicalBlock(scope: !609, file: !1, line: 212, column: 7)
!618 = !DILocation(line: 214, column: 14, scope: !617)
!619 = !DILocation(line: 214, column: 21, scope: !617)
!620 = !DILocation(line: 214, column: 12, scope: !617)
!621 = !DILocation(line: 215, column: 27, scope: !617)
!622 = !DILocation(line: 215, column: 7, scope: !617)
!623 = !DILocation(line: 215, column: 14, scope: !617)
!624 = !DILocation(line: 215, column: 24, scope: !617)
!625 = !DILocation(line: 216, column: 7, scope: !617)
!626 = !DILocation(line: 218, column: 14, scope: !627)
!627 = distinct !DILexicalBlock(scope: !628, file: !1, line: 218, column: 14)
!628 = distinct !DILexicalBlock(scope: !617, file: !1, line: 217, column: 9)
!629 = !DILocation(line: 218, column: 21, scope: !627)
!630 = !DILocation(line: 218, column: 35, scope: !627)
!631 = !DILocation(line: 218, column: 42, scope: !627)
!632 = !DILocation(line: 218, column: 49, scope: !627)
!633 = !DILocation(line: 218, column: 14, scope: !628)
!634 = !DILocation(line: 220, column: 11, scope: !635)
!635 = distinct !DILexicalBlock(scope: !627, file: !1, line: 219, column: 11)
!636 = !DILocation(line: 222, column: 11, scope: !628)
!637 = !DILocation(line: 223, column: 9, scope: !628)
!638 = !DILocation(line: 224, column: 13, scope: !617)
!639 = !DILocation(line: 223, column: 9, scope: !640)
!640 = !DILexicalBlockFile(scope: !628, file: !1, discriminator: 1)
!641 = !DILocation(line: 225, column: 7, scope: !617)
!642 = !DILocation(line: 225, column: 14, scope: !617)
!643 = !DILocation(line: 225, column: 21, scope: !617)
!644 = !DILocation(line: 226, column: 7, scope: !617)
!645 = !DILocation(line: 232, column: 10, scope: !646)
!646 = distinct !DILexicalBlock(scope: !555, file: !1, line: 232, column: 10)
!647 = !DILocation(line: 232, column: 17, scope: !646)
!648 = !DILocation(line: 232, column: 28, scope: !646)
!649 = !DILocation(line: 232, column: 35, scope: !646)
!650 = !DILocation(line: 232, column: 26, scope: !646)
!651 = !DILocation(line: 232, column: 43, scope: !646)
!652 = !DILocation(line: 232, column: 47, scope: !653)
!653 = !DILexicalBlockFile(scope: !646, file: !1, discriminator: 1)
!654 = !DILocation(line: 232, column: 54, scope: !653)
!655 = !DILocation(line: 232, column: 64, scope: !653)
!656 = !DILocation(line: 232, column: 10, scope: !653)
!657 = !DILocation(line: 238, column: 12, scope: !658)
!658 = distinct !DILexicalBlock(scope: !659, file: !1, line: 238, column: 12)
!659 = distinct !DILexicalBlock(scope: !646, file: !1, line: 233, column: 7)
!660 = !DILocation(line: 238, column: 19, scope: !658)
!661 = !DILocation(line: 238, column: 26, scope: !658)
!662 = !DILocation(line: 238, column: 12, scope: !659)
!663 = !DILocation(line: 240, column: 14, scope: !664)
!664 = distinct !DILexicalBlock(scope: !665, file: !1, line: 240, column: 14)
!665 = distinct !DILexicalBlock(scope: !658, file: !1, line: 239, column: 9)
!666 = !DILocation(line: 240, column: 21, scope: !664)
!667 = !DILocation(line: 240, column: 35, scope: !664)
!668 = !DILocation(line: 240, column: 47, scope: !664)
!669 = !DILocation(line: 240, column: 54, scope: !664)
!670 = !DILocation(line: 240, column: 65, scope: !664)
!671 = !DILocation(line: 240, column: 72, scope: !664)
!672 = !DILocation(line: 240, column: 62, scope: !664)
!673 = !DILocation(line: 240, column: 14, scope: !665)
!674 = !DILocation(line: 242, column: 11, scope: !675)
!675 = distinct !DILexicalBlock(scope: !664, file: !1, line: 241, column: 11)
!676 = !DILocation(line: 244, column: 29, scope: !665)
!677 = !DILocation(line: 244, column: 36, scope: !665)
!678 = !DILocation(line: 244, column: 9, scope: !665)
!679 = !DILocation(line: 244, column: 16, scope: !665)
!680 = !DILocation(line: 244, column: 26, scope: !665)
!681 = !DILocation(line: 245, column: 9, scope: !665)
!682 = !DILocation(line: 246, column: 7, scope: !659)
!683 = !DILocation(line: 246, column: 14, scope: !659)
!684 = !DILocation(line: 246, column: 21, scope: !659)
!685 = !DILocation(line: 248, column: 12, scope: !686)
!686 = distinct !DILexicalBlock(scope: !659, file: !1, line: 248, column: 12)
!687 = !DILocation(line: 248, column: 19, scope: !686)
!688 = !DILocation(line: 248, column: 12, scope: !659)
!689 = !DILocation(line: 250, column: 26, scope: !690)
!690 = distinct !DILexicalBlock(scope: !686, file: !1, line: 249, column: 9)
!691 = !DILocation(line: 250, column: 9, scope: !690)
!692 = !DILocation(line: 250, column: 16, scope: !690)
!693 = !DILocation(line: 250, column: 24, scope: !690)
!694 = !DILocation(line: 251, column: 9, scope: !690)
!695 = !DILocation(line: 251, column: 16, scope: !690)
!696 = !DILocation(line: 251, column: 26, scope: !690)
!697 = !DILocation(line: 252, column: 9, scope: !690)
!698 = !DILocation(line: 255, column: 9, scope: !699)
!699 = distinct !DILexicalBlock(scope: !686, file: !1, line: 254, column: 9)
!700 = !DILocation(line: 255, column: 16, scope: !699)
!701 = !DILocation(line: 255, column: 22, scope: !699)
!702 = !DILocation(line: 256, column: 14, scope: !703)
!703 = distinct !DILexicalBlock(scope: !699, file: !1, line: 256, column: 14)
!704 = !DILocation(line: 256, column: 21, scope: !703)
!705 = !DILocation(line: 256, column: 31, scope: !703)
!706 = !DILocation(line: 256, column: 38, scope: !703)
!707 = !DILocation(line: 256, column: 28, scope: !703)
!708 = !DILocation(line: 256, column: 14, scope: !699)
!709 = !DILocation(line: 258, column: 28, scope: !710)
!710 = distinct !DILexicalBlock(scope: !703, file: !1, line: 257, column: 11)
!711 = !DILocation(line: 258, column: 35, scope: !710)
!712 = !DILocation(line: 258, column: 11, scope: !710)
!713 = !DILocation(line: 258, column: 18, scope: !710)
!714 = !DILocation(line: 258, column: 26, scope: !710)
!715 = !DILocation(line: 259, column: 11, scope: !710)
!716 = !DILocation(line: 262, column: 28, scope: !717)
!717 = distinct !DILexicalBlock(scope: !703, file: !1, line: 261, column: 11)
!718 = !DILocation(line: 262, column: 11, scope: !717)
!719 = !DILocation(line: 262, column: 18, scope: !717)
!720 = !DILocation(line: 262, column: 26, scope: !717)
!721 = !DILocation(line: 272, column: 7, scope: !659)
!722 = !DILocation(line: 273, column: 5, scope: !555)
!723 = !DILocation(line: 279, column: 10, scope: !724)
!724 = distinct !DILexicalBlock(scope: !725, file: !1, line: 279, column: 10)
!725 = distinct !DILexicalBlock(scope: !551, file: !1, line: 275, column: 5)
!726 = !DILocation(line: 279, column: 17, scope: !724)
!727 = !DILocation(line: 279, column: 24, scope: !724)
!728 = !DILocation(line: 279, column: 10, scope: !725)
!729 = !DILocation(line: 281, column: 24, scope: !730)
!730 = distinct !DILexicalBlock(scope: !724, file: !1, line: 280, column: 7)
!731 = !DILocation(line: 281, column: 31, scope: !730)
!732 = !DILocation(line: 281, column: 38, scope: !730)
!733 = !DILocation(line: 281, column: 43, scope: !730)
!734 = !DILocation(line: 281, column: 7, scope: !730)
!735 = !DILocation(line: 281, column: 14, scope: !730)
!736 = !DILocation(line: 281, column: 21, scope: !730)
!737 = !DILocation(line: 282, column: 12, scope: !738)
!738 = distinct !DILexicalBlock(scope: !730, file: !1, line: 282, column: 12)
!739 = !DILocation(line: 282, column: 19, scope: !738)
!740 = !DILocation(line: 282, column: 33, scope: !738)
!741 = !DILocation(line: 282, column: 45, scope: !738)
!742 = !DILocation(line: 282, column: 52, scope: !738)
!743 = !DILocation(line: 282, column: 64, scope: !738)
!744 = !DILocation(line: 282, column: 71, scope: !738)
!745 = !DILocation(line: 282, column: 61, scope: !738)
!746 = !DILocation(line: 282, column: 12, scope: !730)
!747 = !DILocation(line: 284, column: 9, scope: !748)
!748 = distinct !DILexicalBlock(scope: !738, file: !1, line: 283, column: 9)
!749 = !DILocation(line: 286, column: 27, scope: !730)
!750 = !DILocation(line: 286, column: 34, scope: !730)
!751 = !DILocation(line: 286, column: 7, scope: !730)
!752 = !DILocation(line: 286, column: 14, scope: !730)
!753 = !DILocation(line: 286, column: 24, scope: !730)
!754 = !DILocation(line: 287, column: 7, scope: !730)
!755 = !DILocation(line: 288, column: 5, scope: !725)
!756 = !DILocation(line: 288, column: 12, scope: !725)
!757 = !DILocation(line: 288, column: 19, scope: !725)
!758 = !DILocation(line: 289, column: 19, scope: !725)
!759 = !DILocation(line: 289, column: 11, scope: !725)
!760 = !DILocation(line: 290, column: 17, scope: !761)
!761 = distinct !DILexicalBlock(scope: !725, file: !1, line: 290, column: 9)
!762 = !DILocation(line: 290, column: 9, scope: !761)
!763 = !DILocation(line: 290, column: 9, scope: !725)
!764 = !DILocation(line: 292, column: 7, scope: !765)
!765 = distinct !DILexicalBlock(scope: !761, file: !1, line: 291, column: 7)
!766 = !DILocation(line: 301, column: 3, scope: !69)
!767 = !DILocation(line: 302, column: 1, scope: !69)
!768 = !DILocalVariable(name: "cdata", arg: 1, scope: !72, file: !1, line: 360, type: !19)
!769 = !DILocation(line: 360, column: 48, scope: !72)
!770 = !DILocalVariable(name: "rat", scope: !72, file: !1, line: 362, type: !7)
!771 = !DILocation(line: 362, column: 21, scope: !72)
!772 = !DILocation(line: 364, column: 23, scope: !72)
!773 = !DILocation(line: 364, column: 30, scope: !72)
!774 = !DILocation(line: 364, column: 39, scope: !72)
!775 = !DILocation(line: 364, column: 3, scope: !72)
!776 = !DILocation(line: 364, column: 10, scope: !72)
!777 = !DILocation(line: 364, column: 21, scope: !72)
!778 = !DILocation(line: 374, column: 6, scope: !779)
!779 = distinct !DILexicalBlock(scope: !72, file: !1, line: 374, column: 6)
!780 = !DILocation(line: 374, column: 13, scope: !779)
!781 = !DILocation(line: 374, column: 22, scope: !779)
!782 = !DILocation(line: 374, column: 6, scope: !72)
!783 = !DILocation(line: 376, column: 11, scope: !784)
!784 = distinct !DILexicalBlock(scope: !779, file: !1, line: 375, column: 5)
!785 = !DILocation(line: 376, column: 18, scope: !784)
!786 = !DILocation(line: 376, column: 28, scope: !784)
!787 = !DILocation(line: 376, column: 9, scope: !784)
!788 = !DILocation(line: 377, column: 8, scope: !789)
!789 = distinct !DILexicalBlock(scope: !784, file: !1, line: 377, column: 8)
!790 = !DILocation(line: 377, column: 12, scope: !789)
!791 = !DILocation(line: 377, column: 8, scope: !784)
!792 = !DILocation(line: 379, column: 11, scope: !793)
!793 = distinct !DILexicalBlock(scope: !789, file: !1, line: 378, column: 7)
!794 = !DILocation(line: 380, column: 7, scope: !793)
!795 = !DILocation(line: 383, column: 13, scope: !796)
!796 = distinct !DILexicalBlock(scope: !789, file: !1, line: 382, column: 7)
!797 = !DILocation(line: 383, column: 20, scope: !796)
!798 = !DILocation(line: 383, column: 31, scope: !796)
!799 = !DILocation(line: 383, column: 29, scope: !796)
!800 = !DILocation(line: 383, column: 11, scope: !796)
!801 = !DILocation(line: 385, column: 5, scope: !784)
!802 = !DILocation(line: 388, column: 12, scope: !803)
!803 = distinct !DILexicalBlock(scope: !779, file: !1, line: 387, column: 5)
!804 = !DILocation(line: 388, column: 19, scope: !803)
!805 = !DILocation(line: 388, column: 28, scope: !803)
!806 = !DILocation(line: 388, column: 36, scope: !803)
!807 = !DILocation(line: 388, column: 43, scope: !803)
!808 = !DILocation(line: 388, column: 34, scope: !803)
!809 = !DILocation(line: 388, column: 9, scope: !803)
!810 = !DILocation(line: 390, column: 8, scope: !811)
!811 = distinct !DILexicalBlock(scope: !72, file: !1, line: 390, column: 8)
!812 = !DILocation(line: 390, column: 14, scope: !811)
!813 = !DILocation(line: 390, column: 21, scope: !811)
!814 = !DILocation(line: 390, column: 12, scope: !811)
!815 = !DILocation(line: 390, column: 8, scope: !72)
!816 = !DILocation(line: 392, column: 20, scope: !817)
!817 = distinct !DILexicalBlock(scope: !811, file: !1, line: 391, column: 5)
!818 = !DILocation(line: 392, column: 5, scope: !817)
!819 = !DILocation(line: 392, column: 12, scope: !817)
!820 = !DILocation(line: 392, column: 18, scope: !817)
!821 = !DILocation(line: 393, column: 5, scope: !817)
!822 = !DILocation(line: 396, column: 5, scope: !823)
!823 = distinct !DILexicalBlock(scope: !811, file: !1, line: 395, column: 5)
!824 = !DILocation(line: 396, column: 12, scope: !823)
!825 = !DILocation(line: 396, column: 18, scope: !823)
!826 = !DILocation(line: 403, column: 14, scope: !823)
!827 = !DILocation(line: 403, column: 33, scope: !823)
!828 = !DILocation(line: 403, column: 40, scope: !823)
!829 = !DILocation(line: 403, column: 5, scope: !823)
!830 = !DILocation(line: 404, column: 5, scope: !823)
!831 = !DILocation(line: 404, column: 12, scope: !823)
!832 = !DILocation(line: 404, column: 21, scope: !823)
!833 = !DILocation(line: 405, column: 5, scope: !823)
!834 = !DILocation(line: 405, column: 12, scope: !823)
!835 = !DILocation(line: 405, column: 22, scope: !823)
!836 = !DILocation(line: 406, column: 19, scope: !837)
!837 = distinct !DILexicalBlock(scope: !823, file: !1, line: 406, column: 10)
!838 = !DILocation(line: 406, column: 11, scope: !837)
!839 = !DILocation(line: 406, column: 10, scope: !823)
!840 = !DILocation(line: 408, column: 7, scope: !841)
!841 = distinct !DILexicalBlock(scope: !837, file: !1, line: 407, column: 7)
!842 = !DILocation(line: 417, column: 3, scope: !72)
!843 = !DILocation(line: 418, column: 1, scope: !72)
!844 = !DILocalVariable(name: "cdata", arg: 1, scope: !65, file: !1, line: 507, type: !19)
!845 = !DILocation(line: 507, column: 60, scope: !65)
!846 = !DILocation(line: 512, column: 16, scope: !847)
!847 = distinct !DILexicalBlock(scope: !65, file: !1, line: 512, column: 8)
!848 = !DILocation(line: 512, column: 33, scope: !847)
!849 = !DILocation(line: 512, column: 40, scope: !847)
!850 = !DILocation(line: 512, column: 9, scope: !847)
!851 = !DILocation(line: 512, column: 8, scope: !65)
!852 = !DILocation(line: 514, column: 5, scope: !853)
!853 = distinct !DILexicalBlock(scope: !847, file: !1, line: 513, column: 5)
!854 = !DILocation(line: 516, column: 3, scope: !65)
!855 = !DILocation(line: 516, column: 10, scope: !65)
!856 = !DILocation(line: 516, column: 19, scope: !65)
!857 = !DILocation(line: 517, column: 16, scope: !858)
!858 = distinct !DILexicalBlock(scope: !65, file: !1, line: 517, column: 8)
!859 = !DILocation(line: 517, column: 9, scope: !858)
!860 = !DILocation(line: 517, column: 8, scope: !65)
!861 = !DILocation(line: 519, column: 5, scope: !862)
!862 = distinct !DILexicalBlock(scope: !858, file: !1, line: 518, column: 5)
!863 = !DILocation(line: 522, column: 6, scope: !864)
!864 = distinct !DILexicalBlock(scope: !65, file: !1, line: 522, column: 6)
!865 = !DILocation(line: 522, column: 13, scope: !864)
!866 = !DILocation(line: 522, column: 25, scope: !864)
!867 = !DILocation(line: 522, column: 32, scope: !864)
!868 = !DILocation(line: 522, column: 23, scope: !864)
!869 = !DILocation(line: 522, column: 6, scope: !65)
!870 = !DILocation(line: 524, column: 5, scope: !871)
!871 = distinct !DILexicalBlock(scope: !864, file: !1, line: 523, column: 5)
!872 = !DILocation(line: 526, column: 3, scope: !65)
!873 = !DILocation(line: 527, column: 1, scope: !65)
